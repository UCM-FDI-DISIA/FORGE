#include "SceneManager.h"
#include "Scene.h"
#include "Entity.h"
#include "Component.h"
#include "EntityData.h"
#include <lua.hpp>
#pragma warning(push)
#pragma warning(disable : 26439)
#include <LuaBridge/LuaBridge.h>
#pragma warning(pop)
#include "ForgeError.h"

std::unique_ptr<SceneManager> SceneManager::instance = nullptr;
bool SceneManager::initialised = false;

SceneManager::SceneManager() : 
	activeScene("",nullptr),
	lua(nullptr) {
	groups.insert({"default",0});
}

Entity* SceneManager::addEntity(Scene* scene, EntityData* data) {

	std::unordered_map<Component*, ComponentData*> initData;
	Entity* entity = scene->addEntity(getGroupId(data->group));
	if (data->handler != "") {
		scene->setHandler(data->handler, entity);
	}
	for (auto& componentData : data->components) {
		Component* component = entity->addComponent(componentData.first);
		if(component != nullptr) {
			initData.insert({ component, componentData.second });
		}
	}
	for (auto& childData : data->children) {
		if (childData != nullptr) {
			Entity* child = addEntity(scene, childData);
			if (!child->isAlive()) {
				entity->setAlive(false);
			}
			entity->addChild(child);
		}
	}
	for (auto& componentInit : initData) {
		if (!componentInit.first->initSerialized(componentInit.second)) {
			entity->setAlive(false);
		}
	}
	for (auto& componentInit : initData) {
		if (!componentInit.first->initComponent(componentInit.second)) {
			entity->setAlive(false);
		}
	}

	return entity;

}

void SceneManager::Init() {
	instance = std::unique_ptr<SceneManager>(new SceneManager());
	initialised = true;
}

SceneManager* SceneManager::GetInstance() {
	if (initialised) return instance.get();
	return nullptr;
}

SceneManager::~SceneManager() {

}

void SceneManager::cleanUp() {
	for (auto& scene : loadedScenes) {
		delete scene.second;
	}
	for (auto& scene : sceneBlueprints) {
		for (auto& entity : scene.second) {
			if (!entity->isBlueprint) {
				delete entity;
			}
		}
	}
	for (auto& entity : entityBlueprints) {
		delete entity.second;
	}
}

void SceneManager::setLuaState(lua_State* L) {
	lua = L;
}

lua_State* SceneManager::getLuaState() {
	return lua;
}

bool SceneManager::changeScene(std::string const& scene, bool renewScene) {
	Scene*& activeScenePointer = activeScene.second;
	Scene* newScene;
	if (activeScenePointer != nullptr) {
		activeScenePointer->setEnabled(false);
	}
	auto iter = loadedScenes.find(scene);
	if (iter == loadedScenes.end()) {
		newScene = createScene(scene);
	}
	else {
		if (renewScene) {
			delete iter->second;
			loadedScenes.erase(iter);
			newScene = createScene(scene);
		}
		else {
			newScene = iter->second;
			newScene->setEnabled(true);
		}
	}
	if (newScene != nullptr) {
		activeScene = { scene, newScene };
		return true;
	}
	throwError(false, "La escena no se ha encontrado o no se ha podido iniciar correctamente.");
}

void SceneManager::removeScene(std::string const& id) {
	auto iter = loadedScenes.find(id);
	if (iter != loadedScenes.end()) {
		delete iter->second;
		loadedScenes.erase(iter);
	}
}

Scene* SceneManager::createScene(std::string const& id) {
	auto iter = sceneBlueprints.find(id);
	if (iter == sceneBlueprints.end()) {
		throwError(nullptr, "Si una escena no aparece en los archivos, no existe.");
	}
	Scene* newScene = new Scene();
	for (EntityData* entity : iter->second) {
		if (!addEntity(newScene, entity)->isAlive()) {
			reportError("No se ha podido crear la entidad.");
		}
	}
	loadedScenes.insert({ id, newScene });
	return newScene;
}

Scene* SceneManager::getScene(std::string const& id) {
	auto iter = loadedScenes.find(id);
	if (iter != loadedScenes.end()) {
		return loadedScenes[id];
	}
	return nullptr;
}

const std::string& SceneManager::getActiveSceneId() const{
	return activeScene.first;
}

int SceneManager::getMaxGroupId() {
	return static_cast<int>(groups.size());
}

bool SceneManager::update(double dt) {
	if (activeScene.second != nullptr && !activeScene.second->getEndScene()) {
		activeScene.second->update(dt);
		return true;
	}
	return false;
}

void SceneManager::fixedUpdate() {
	activeScene.second->fixedUpdate();
}

void SceneManager::refresh() {
	activeScene.second->refresh();
}

int SceneManager::getGroupId(std::string const& group) {
	return groups[group];
}

void SceneManager::addSceneBlueprint(std::string const& id, std::vector<EntityData*> const& scene) {
	sceneBlueprints.insert({ id,scene });
}

void SceneManager::addEntityBlueprint(std::string const& id, EntityData* entity) {
	entityBlueprints.insert({ id,entity });
}

EntityData* SceneManager::getEntityBlueprint(std::string const& id) {
	auto iter = entityBlueprints.find(id);
	if (iter != entityBlueprints.end()) {
		return entityBlueprints[id];
	}
	return nullptr;
}


void SceneManager::addGroup(std::string const& group) {
	groups.insert({ group, getMaxGroupId()});
}