#include "SceneManager.h"
#include "Scene.h"
#include "Entity.h"
#include "Component.h"
#include "ComponentData.h"
#include "EntityData.h"
#include <lua.hpp>
#pragma warning(push)
#pragma warning(disable : 26439)
#include <LuaBridge/LuaBridge.h>
#pragma warning(pop)
#include "Transform.h"
#include "ForgeError.h"

std::unique_ptr<SceneManager> SceneManager::instance = nullptr;
bool SceneManager::initialised = false;

SceneManager::SceneManager() : 
	activeScene("",nullptr),
	lua(nullptr) {
	groups.insert({"default",0});
}

Entity* SceneManager::addEntity(Scene* scene, EntityData* data) {

	Entity* entity = scene->addEntity(getGroupId(data->group));
	if (data->handler != "") {
		scene->setHandler(data->handler, entity);
	}
	if (data->keepBetweenScenes) {
		entity->setKeepBetweenScenes(true);
	}
	for (auto& componentData : data->components) {
		if (componentData != nullptr) {
			Component* component = entity->addComponent(componentData->getId());
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
	if (!entity->initSerializedComponents(data->components)) {
		entity->setAlive(false);
	}
	if (!entity->initComponents(data->components)) {
		entity->setAlive(false);
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

Entity* SceneManager::instantiateBlueprint(std::string bluePrintId) {
	EntityData* data = getEntityBlueprint(bluePrintId);
	if (data == nullptr) {
		throwError(nullptr, "No se ha encontrado el BluePrint espeficiado.");
	}
	Scene*& scene = activeScene.second;
	Entity* entity = addEntity(scene, data);
	if (entity->isAlive()) {
		return entity;
	}
	throwError(nullptr, "La entidad no se ha instanciado correctamente.");
}

Entity* SceneManager::instantiateBlueprint(std::string bluePrintId, forge::Vector3 newPos) {
	Entity* entity = instantiateBlueprint(bluePrintId);
	if (entity != nullptr) {
		if (entity->hasComponent(Transform::id)) {
			entity->getComponent<Transform>()->setPosition(newPos);
		}
		else reportError("La entidad no tiene Transform.");
	}
	return entity;
}

bool SceneManager::changeScene(std::string const& scene, bool renewScene) {
	Scene*& activeScenePointer = activeScene.second;
	Scene* newScene;
	std::vector<Entity*> keptEntities;
	if (activeScenePointer != nullptr) {
		keptEntities = activeScenePointer->disableScene();
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
			newScene->enableScene();
		}
	}
	if (newScene != nullptr) {
		for (Entity* entity : keptEntities) {
			newScene->addEntity(entity);
		}
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

Scene* SceneManager::getActiveScene() {
	return activeScene.second;
}

const std::string& SceneManager::getActiveSceneId() const{
	return activeScene.first;
}

int SceneManager::getMaxGroupId() {
	return static_cast<int>(groups.size());
}

bool SceneManager::update() {
	if (activeScene.second != nullptr) {
		activeScene.second->update();
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