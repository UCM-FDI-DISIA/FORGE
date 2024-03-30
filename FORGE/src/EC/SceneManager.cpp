#include "SceneManager.h"
#include "Scene.h"
#include "Entity.h"
#include "Component.h"
#include "EntityData.h"
#include "lua.hpp"
#include "LuaBridge/LuaBridge.h"

std::unique_ptr<SceneManager> SceneManager::instance = nullptr;

SceneManager::SceneManager() : 
	activeScene(nullptr),
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
		initData.insert({ component,componentData.second });
	}
	for (auto& childData : data->children) {
		if (childData != nullptr) {
			Entity* child = addEntity(scene, childData);
			if (!child->isAlive()) entity->setAlive(false);
			entity->addChild(child);
		}
	}
	for (auto& componentInit : initData) {
		if (componentInit.first->initSerialized(componentInit.second)) {
			// Si un componente se inicializa mal no se inicia la escena
			if (!componentInit.first->initComponent(componentInit.second)) {
				entity->setAlive(false);
			}
		}
		else {
			entity->setAlive(false);
		}
	}
	return entity;

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
	lua_close(lua);
}

SceneManager* SceneManager::getInstance() {
    if (instance.get() != nullptr) return instance.get();
	return (instance = std::unique_ptr<SceneManager>(new SceneManager())).get();
}

void SceneManager::setLuaState(lua_State* L) {
	lua = L;
}

lua_State* SceneManager::getLuaState() {
	return lua;
}

void SceneManager::changeScene(std::string scene, bool renewScene) {
	Scene* newScene;
	auto iter = loadedScenes.find(scene);
	if (activeScene != nullptr) {
		activeScene->setEnabled(false);
	}
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
		activeScene = newScene;
	}
	else if (activeScene != nullptr) {
		activeScene->setEnabled(true);
	}
	if (activeScene == nullptr || activeScene->getEndScene() == true) std::cerr << "ERROR: La escena no se ha encontrado o no se ha podido iniciar correctamente\n";
}

void SceneManager::removeScene(std::string id) {
	auto iter = loadedScenes.find(id);
	if (iter != loadedScenes.end()) {
		delete iter->second;
		loadedScenes.erase(iter);
	}
}

Scene* SceneManager::createScene(std::string id)
{
	auto iter = sceneBlueprints.find(id);
	if (iter == sceneBlueprints.end()) {
		std::cerr << "ERROR: Si una escena no aparece en los archivos, no existe" << std::endl;
		return nullptr;
	}
	Scene* newScene = new Scene();
	for (EntityData* entity : iter->second) {
		if (!addEntity(newScene, entity)->isAlive()) {
			newScene->endScene();
		}
	}
	loadedScenes.insert({ id, newScene });
	return newScene;
}

Scene* SceneManager::getScene(std::string id) {
	auto iter = loadedScenes.find(id);
	if (iter != loadedScenes.end()) {
		return loadedScenes[id];
	}
	return nullptr;
}

int SceneManager::getMaxGroupId() {
	return static_cast<int>(groups.size());
}

bool SceneManager::update() {
	if (activeScene != nullptr) activeScene->update();
	// Devuelve false en caso de que endScene sea true o la escena sea nula
	return (activeScene != nullptr) ? !activeScene->getEndScene() : false;
}

void SceneManager::refresh() {
	activeScene->refresh();
}

int SceneManager::getGroupId(std::string group) {
	return groups[group];
}

void SceneManager::addSceneBlueprint(std::string id, std::vector<EntityData*> scene) {
	sceneBlueprints.insert({ id,scene });
}

void SceneManager::addEntityBlueprint(std::string id, EntityData* entity) {
	entityBlueprints.insert({ id,entity });
}

EntityData* SceneManager::getEntityBlueprint(std::string id) {
	auto iter = entityBlueprints.find(id);
	if (iter != entityBlueprints.end()) {
		return entityBlueprints[id];
	}
	return nullptr;
}


void SceneManager::addGroup(std::string group) {
	groups.insert({ group, getMaxGroupId()});
}