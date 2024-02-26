#pragma once
#ifndef SCENE_MANAGER_H_
#define SCENE_MANAGER_H_
#include <list>
#include <memory>
#include <unordered_map>
#include <string>

struct EntityData;
class Scene;
class Entity;

class SceneManager {
private:
    static std::unique_ptr<SceneManager> instance;

	Scene* activeScene;
	std::unordered_map<std::string, Scene*> loadedScenes;

	std::unordered_map<std::string, EntityData*> entityBlueprints;
	std::unordered_map<std::string, std::vector<EntityData*>> sceneBlueprints;

	std::unordered_map<std::string, int> groups;
	int maxGroupId;

    SceneManager();

public:
	~SceneManager();
	/// <summary>
	/// Devuelve la instancia de SceneManager y si no existe la crea
	/// </summary>
	/// <returns>Instancia singleton a SceneManager</returns>
	static SceneManager* getInstance();
	/// <summary>
	/// Cambia la escena activa a una con el identificador del parametro
	/// Si no hay ninguna cargada en memoria la crea a traves de su blueprint
	/// </summary>
	/// <param name="scene">Identificador de la escena</param>
	/// <param name="renewScene">
	/// Elimina la escena cargada en memoria y la crea de nuevo desde el blueprint
	/// </param>
	void changeScene(std::string scene, bool renewScene = false);
	/// <summary>
	/// Elimina una escena cargada en memoria
	/// </summary>
	/// <param name="id">Identificador de la escena</param>
	void removeScene(std::string id);
	/// <summary>
	/// Crea una escena a partir de un blueprint
	/// </summary>
	/// <param name="id">Identificador del blueprint</param>
	/// <returns>La escena creada</returns>
	Scene* createScene(std::string id);
	/// <returns>
	/// Una escena a partir de su Identificador
	/// </returns>
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
	/// <summary>
	/// Agrega un blueprint de escena y lo mapea con su id
	/// </summary>
	/// <param name="id">Identificador del blueprint</param>
	/// <param name="scene">Blueprint de la escena</param>
	void addSceneBlueprint(std::string id, std::vector<EntityData*> scene);
	/// <summary>
	/// Agrega un blueprint de entidad y lo mapea con su id
	/// </summary>
	/// <param name="id">Identificador del blueprint</param>
	/// <param name="entity">Blueprint de la entidad</param>
	void addEntityBlueprint(std::string id, EntityData* entity);
	/// <param name="id">Identificador del Blueprint de entidad </param>
	/// <returns>Puntero al Blueprint de la entidad</returns>
	EntityData* getEntityBlueprint(std::string id);

	

};
#endif // !SCENE_MANAGER_H_