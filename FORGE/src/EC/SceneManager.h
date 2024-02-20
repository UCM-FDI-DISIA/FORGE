#pragma once
#ifndef SCENE_MANAGER_H_
#define SCENE_MANAGER_H_
#include <list>
#include <memory>
#include <unordered_map>
#include <string>

struct EntityStruct;
class Scene;
class Entity;

class SceneManager {
private:
    static std::unique_ptr<SceneManager> instance;

	Scene* activeScene;
	std::unordered_map<std::string, Scene*> loadedScenes;

	std::unordered_map<std::string, EntityStruct*> entityBlueprints;
	std::unordered_map<std::string, std::vector<EntityStruct*>> sceneBlueprints;

	std::unordered_map<std::string, int> groups;
	int maxGroupId;

    SceneManager();

public:
	static SceneManager* getInstance();

	void changeScene(std::string scene, bool renewScene = false);
	void removeScene(std::string id);
	Scene* createScene(std::string id);
	Scene* getScene(std::string id);
	/// <returns>
	/// Cantidad total de grupos
	/// </returns>
	int getMaxGroupId();
	/// <summary>
	/// Devuelve la id de un grupo a partir de su nombre
	/// </summary>
	/// <param name="group">Nombre del grupo</param>
	/// <returns>Id del grupo</returns>
	int getGroupId(std::string group);
	void addSceneBlueprint(std::string id, std::vector<EntityStruct*> scene);
	void addEntityBlueprint(std::string id, EntityStruct* entity);

	

};
#endif // !SCENE_MANAGER_H_