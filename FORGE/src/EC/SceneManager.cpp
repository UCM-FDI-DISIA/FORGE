#include "SceneManager.h"
#include "Scene.h"

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
	delete loadedScenes[id];
	loadedScenes.erase(id);
}

Scene* SceneManager::createScene(std::string id)
{
	//createSceneFromLuaData(sceneBlueprints[id]);
	return nullptr;
}

Scene* SceneManager::getScene(std::string id) {
	auto scnIt = loadedScenes.find(id);
	if (scnIt != loadedScenes.end()) {
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

void SceneManager::addEntityBlueprint(std::string id, EntityStruct* entity)
{
	entityBlueprints.insert({ id,entity });
}
