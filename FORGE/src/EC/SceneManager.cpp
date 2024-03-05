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
}

Entity* SceneManager::addEntity(Scene* scene, EntityData* data) {
	std::unordered_map<Component*, ComponentData*> initData;
	Entity* entity = scene->addEntity(getGroupId(data->group));
	if (data->handler != "") {
		scene->setHandler(data->handler,entity);
	}
	for (auto& componentData : data->components) {
		Component* component = entity->addComponent(componentData.first);
		initData.insert({ component,componentData.second });
	}
	for (auto& childData : data->children) {
		if (childData != nullptr) {
			Entity* child = addEntity(scene, childData);
			entity->addChild(child);
		}
	}
	for (auto& componentInit : initData) {
		componentInit.first->initSerialized(componentInit.second);
		componentInit.first->initComponent(componentInit.second);
	}

}

SceneManager::~SceneManager() {
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
	auto iter = loadedScenes.find(scene);
	if (iter == loadedScenes.end()) {
		activeScene = createScene(scene);
	}
	else {
		if (renewScene) {
			delete iter->second;
			loadedScenes.erase(iter);
			activeScene = createScene(scene);
		}
		else {
			activeScene = iter->second;
		}
	}
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
		return nullptr;
	}
	Scene* newScene = new Scene();
	for (EntityData* entity : iter->second) {
		addEntity(newScene, entity);
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