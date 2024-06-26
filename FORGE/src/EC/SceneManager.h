#pragma once
#ifndef SCENE_MANAGER_H_
#define SCENE_MANAGER_H_
#include <list>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <utility>
#include "Vector3.h"
#include "ForgeExport.h"

struct EntityData;
class Scene;
class Entity;
class Transform;
class ComponentData;
struct lua_State;

class SceneManager {
private:
	struct EntityPair {
		Entity* entity = nullptr;
		EntityData* data = nullptr;
		std::vector<EntityPair*> children;
		~EntityPair();
	};

    static std::unique_ptr<SceneManager> instance;
	static bool initialised;

	std::pair<std::string, Scene*> activeScene;
	std::unordered_map<std::string, Scene*> loadedScenes;
	std::pair<std::string, bool> sceneToChange;

	std::unordered_map<std::string, EntityData*> entityBlueprints;
	std::unordered_map<std::string, std::vector<EntityData*>> sceneBlueprints;
	std::vector<EntityData*> keptBetweenScenes;

	std::unordered_map<std::string, int> groups;

	lua_State* lua;

    SceneManager();

	/// <summary>
	/// Agrega una nueva entidad sin inicializar a la escena escena pasada
	/// </summary>
	/// <param name="scene">Escena a la que agregar la entidad</param>
	/// <param name="data">Datos de la entidad a agregar</param>
	/// <returns>Puntero de una pareja con la entidad generada y su data</returns>
	EntityPair* addEntity(Scene* scene, EntityData* data);
	/// <summary>
	/// Inicializa los componentes de la entidad y sus hijos
	/// </summary>
	/// <param name="pair">Puntero a la pareja que contiene la Entidad y su EntityData</param>
	/// <returns>Puntero a la entidad inicializada</returns>
	Entity* initEntity(EntityPair* pair);
	/// <summary>
	/// Instancia en escena una Entidad a partir del EntityData de un blueprint
	/// </summary>
	/// <param name="data">Data del blueprint a copiar</param>
	/// <returns>Puntero a la entidad generada</returns>
	EntityPair* instantiateBlueprint(EntityData* data);
	/// <summary>
	/// Efectua el cambio de escena a aquella marcada como nueva escena a iniciar
	/// </summary>
	/// <returns>Booleano que indica si se ha podido cambiar correctamente</returns>
	bool doChangeScene();
	/// <summary>
	/// Inicializa las entidades pasadas y limpia su escena de posibles fallos de inicializacion
	/// </summary>
	/// <param name="scene">Escena de las entidades a inicializar</param>
	/// <param name="initData">Entidades a inicializar</param>
	void initScene(Scene* scene, std::unordered_set<EntityPair*>& initData);

public:
	/// <summary>
	/// Crea una instancia del SceneManager
	/// </summary>
	FORGE_API static void Init();
	/// <summary>
	/// Devuelve la instancia de SceneManager y si no existe devuelve un puntero a nulo
	/// </summary>
	/// <returns>Instancia singleton a SceneManager. nullptr si no se ha inicializado</returns>
	FORGE_API static SceneManager* GetInstance();
	SceneManager(SceneManager const&) = delete;
	void operator=(SceneManager const&) = delete;
	/// <summary>
	/// Destruye la instancia
	/// </summary>
	FORGE_API ~SceneManager();
	/// <summary>
	/// Destruye las escenas cargadas y las plantillas de escena y entidades guardadas
	/// </summary>
	FORGE_API void cleanUp();
	/// <summary>
	/// Establece el lua_State usado para la carga de EC
	/// </summary>
	/// <param name="L">Puntero al lua_State usado para la carga de EC</param>
	FORGE_API void setLuaState(lua_State* L);
	/// <summary>
	/// Devuelve un puntero al lua_State guardado
	/// </summary>
	/// <returns>Puntero al lua_State guardado o nullptr si no se a inicializado</returns>
	FORGE_API lua_State* getLuaState();
	/// <summary>
	/// Instancia un blueprint en escena
	/// </summary>
	/// <param name="bluePrintId">Identificador del blueprint</param>
	/// <returns>Un puntero a la entidad instanciada. nullptr si no existia el blueprint o era invalido</returns>
	FORGE_API Entity* instantiateBlueprint(std::string const& bluePrintId);
	/// <summary>
	/// Instancia un blueprint en escena en la posicion indicada
	/// </summary>
	/// <param name="bluePrintId">Identificador del blueprint</param>
	/// <param name="newPos">Posicion para el blueprint</param>
	/// <returns>Un puntero a la entidad instanciada. nullptr si no existia el blueprint o era invalido</returns>
	FORGE_API Entity* instantiateBlueprint(std::string const& bluePrintId, forge::Vector3 const& newPos);
	/// <summary>
	/// Instancia un blueprint en escena en la posicion indicada
	/// </summary>
	/// <param name="bluePrintId">Identificador del blueprint</param>
	/// <param name="parent">Entidad padre del blueprint instanciado</param>
	/// <returns>Un puntero a la entidad instanciada. nullptr si no existia el blueprint o era invalido</returns>
	FORGE_API Entity* instantiateBlueprint(std::string const& bluePrintId, Entity* parent);
	/// <summary>
	/// Instancia un blueprint en escena en la posicion indicada con una entidad padre
	/// </summary>
	/// <param name="bluePrintId">Identificador del blueprint</param>
	/// <param name="newPos">Posicion para el blueprint</param>
	/// <param name="parent">Entidad padre del blueprint instanciado</param>
	/// <returns>Un puntero a la entidad instanciada. nullptr si no existia el blueprint o era invalido</returns>
	FORGE_API Entity* instantiateBlueprint(std::string const& bluePrintId, forge::Vector3 const& newPos, Entity* parent);
	/// <summary>
	/// Cambia la escena activa a una con el identificador del parametro
	/// Si no hay ninguna cargada en memoria la crea a traves de su blueprint
	/// </summary>
	/// <param name="scene">Identificador de la escena</param>
	/// <param name="renewScene">
	/// Elimina la escena cargada en memoria y la crea de nuevo desde el blueprint
	/// </param>
	/// <returns>Booleano que indica si se cambia de escena correctamente</returns>
	FORGE_API bool changeScene(std::string const& scene, bool renewScene = false);
	/// <summary>
	/// Elimina una escena cargada en memoria
	/// </summary>
	/// <param name="id">Identificador de la escena</param>
	FORGE_API void removeScene(std::string const& id);
	/// <summary>
	/// Crea una escena a partir de un blueprint
	/// </summary>
	/// <param name="id">Identificador del blueprint</param>
	/// <returns>La escena creada</returns>
	FORGE_API std::pair<Scene*, std::unordered_set<EntityPair*>> createScene(std::string const& id);
	/// <summary>
	/// Crea y activa la primera escena del juego
	/// </summary>
	/// <param name="id">Id de la escena a cargar</param>
	/// <returns>Booleano que indica si la creacion fue correcta</returns>
	FORGE_API bool createFirstScene(std::string const& id);
	/// <returns>
	/// Una escena a partir de su Identificador
	/// </returns>
	FORGE_API Scene* getScene(std::string const& id);
	/// <returns>
	/// Devuelve la escena en ejecucion
	/// </returns>
	FORGE_API Scene* getActiveScene() const;
	/// <summary>
	/// Devuelve el identificador de la escena activa
	/// </summary>
	FORGE_API std::string const& getActiveSceneId() const;
	/// <returns>
	/// Cantidad total de grupos
	/// </returns>
	FORGE_API int getMaxGroupId();
	/// <returns>
	/// Actualiza las entidades de la escena activa
	/// </returns>
	FORGE_API bool update();
	/// <summary>
	///	Actualiza las entidades de la escena activa en periodos de tiempo fijos
	/// </summary>
	FORGE_API void fixedUpdate();
	/// <summary>
	/// Devuelve la id de un grupo a partir de su nombre
	/// </summary>
	/// <param name="group">Nombre del grupo</param>
	/// <returns>Id del grupo</returns>
	FORGE_API int getGroupId(std::string const& group);
	/// <summary>
	/// Agrega un blueprint de escena y lo mapea con su id
	/// </summary>
	/// <param name="id">Identificador del blueprint</param>
	/// <param name="scene">Blueprint de la escena</param>
	FORGE_API void addSceneBlueprint(std::string const& id, std::vector<EntityData*> const& scene);
	/// <summary>
	/// Agrega un blueprint de una entidad para que se mantenga entre escenas
	/// </summary>
	/// <param name="kbsData">Blueprint de la entidad que se mantendra entre escenas</param>
	FORGE_API void addKeptBetweenScenes(EntityData* kbsData);
	/// <summary>
	/// Agrega un blueprint de entidad y lo mapea con su id
	/// </summary>
	/// <param name="id">Identificador del blueprint</param>
	/// <param name="entity">Blueprint de la entidad</param>
	FORGE_API void addEntityBlueprint(std::string const& id, EntityData* entity);
	/// <param name="id">Identificador del Blueprint de entidad </param>
	/// <returns>Puntero al Blueprint de la entidad</returns>
	FORGE_API EntityData* getEntityBlueprint(std::string const& id);
	/// <summary>
	/// Guarda un nuevo grupo de entidades que no se haya guardado
	/// </summary>
	/// <param name="group">Identificador del grupo nuevo</param>
	FORGE_API void addGroup(std::string const& group);

};
#endif // !SCENE_MANAGER_H_