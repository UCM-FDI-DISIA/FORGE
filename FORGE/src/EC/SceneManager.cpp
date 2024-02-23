#include "SceneManager.h"
#include "Scene.h"
#include "Entity.h"
#include "../Load/EcsLoad.h"

SceneManager* SceneManager::getInstance() {
    if (instance.get() != nullptr) return instance.get();
	return (instance = std::unique_ptr<SceneManager>(new SceneManager())).get();
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
	for (EntityStruct* e : iter->second) {
		Entity* ent = newScene->addEntity(getGroupId(e->group));
		if (e->handler != "") {
			newScene->setHandler(e->handler,ent);
		}
		for (auto& c : e->components) {
			ent->addComponent(c.first, &(c.second));
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
	return maxGroupId;
}

int SceneManager::getGroupId(std::string group) {
	return groups[group];
}

void SceneManager::addSceneBlueprint(std::string id, std::vector<EntityStruct*> scene)
{
	sceneBlueprints.insert({ id,scene });
}

void SceneManager::addEntityBlueprint(std::string id, EntityStruct entity)
{
	entityBlueprints.insert({ id,entity });
}

EntityStruct const SceneManager::getEntityBlueprint(std::string id)
{
	auto iter = entityBlueprints.find(id);
	if (iter != entityBlueprints.end()) {
		return entityBlueprints[id];
	}
}
