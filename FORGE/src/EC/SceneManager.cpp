#include "SceneManager.h"
#include "Scene.h"

SceneManager* SceneManager::getInstance() {
    if (instance.get() != nullptr) return instance.get();
	return (instance = std::unique_ptr<SceneManager>(new SceneManager())).get();
}

void SceneManager::changeScene(std::string scene, bool renewScene)
{
	Scene* targetScene = nullptr;
	if (renewScene || !(targetScene = loadedScenes.find(scene)->second)) {
		targetScene = createScene(scene);
	}
	activeScene = targetScene;
}

void SceneManager::removeScene(std::string id)
{
	delete loadedScenes[id];
	loadedScenes.erase(id);
}

Scene* SceneManager::createScene(std::string id)
{
	//createSceneFromLuaData(sceneBlueprints[id]);
	return nullptr;
}

int SceneManager::getMaxGroupId()
{
	return maxGroupId;
}

int SceneManager::getGroupId(std::string group)
{
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
