#pragma once
#ifndef ENTITY_H_
#define ENTITY_H_
#include <unordered_map>
#include <string>
#include <unordered_set>
#include "ForgeExport.h"

class Scene;
class Component;
class Entity;
class Factory;
class ComponentData;
class Invoker;

class Entity {
private:
	Invoker* inv;
	Factory& fact;
	Scene* scene;
	std::vector<Component*> components;
	std::unordered_map<std::string, Component*> componentMap;
	Entity* parent;
	std::unordered_set<Entity*> children;
	int groupId;
	bool alive;
	bool keepBetweenScenes;

	/// <summary>
	/// Establece cual es la Entity padre de esta Entity.
	/// </summary>
	/// <param name="parent">Puntero a la Entity que se establece como padre.</param>
	/// <returns>Puntero a la Entity que se establece como padre.</returns>
	Entity* setParent(Entity* parent);
	/// <summary>
	/// Establece el parent de la entidad como nullptr
	/// </summary>
	void removeParent();
public:
	/// <summary>
	/// Constructor por defecto de la clase Entity
	/// </summary>
	FORGE_API Entity();
	/// <summary>
	/// Destructor por defecto de la clase Entity
	/// </summary>
	FORGE_API ~Entity();
	/// <summary>
	/// Asigna la Scene en la que esta el componente y el group al que pertenece
	/// </summary>
	/// <param name="_scene">Referencia a la escena de la Entity</param>
	/// <param name="_group">Referencia al grupo de la Entity</param>
	FORGE_API void setContext(Scene* _scene, int _groupId);
	/// <returns>
	/// Booleano que indica si la Entity esta viva
	/// </returns>
	FORGE_API bool isAlive();
	/// <summary>
	/// Asigna si la Entity esta viva o no, de cara al recolector de basura
	/// </summary>
	/// <param name="_alive">Nuevo estado de vida de la entidad</param>
	FORGE_API void setAlive(bool _alive);
	/// <summary>
	/// Agrega el Component dicho a la Entity
	/// </summary>
	/// <param name="data">Identificador del componente</param>
	/// <returns>Un puntero al Component agregado</returns>
	FORGE_API Component* addComponent(std::string const& id);
	/// <summary>
	/// Agrega el Component dicho a la Entity y lo inicializa
	/// </summary>
	/// <returns>Un puntero al Component agregado</returns>
	/// <param name="data">Informacion del componente en formato de object de Lua</param>
	FORGE_API Component* addComponent(ComponentData* data);
	/// <summary>
	/// Inicializa todos los componentes de la entidad
	/// </summary>
	/// <param name="data">Vector con los datos de la inicializacion</param>
	/// <returns>Booleano que indica si la inicializacion ha sido correcta</returns>
	FORGE_API bool initComponents(std::vector<ComponentData*> data);
	/// <summary>
	/// Inicializa todos los componentes de la entidad
	/// </summary>
	/// <param name="data">Vector con los datos de la inicializacion de componentes serializados</param>
	/// <returns>Booleano que indica si la inicializacion ha sido correcta</returns>
	FORGE_API bool initSerializedComponents(std::vector<ComponentData*> data);
	/// <summary>
	/// Agrega una nueva Entity como hija de this, y establece this como el padre de la hija.
	/// </summary>
	/// <param name="child">Puntero a la Entity hija.</param>
	/// <returns>Puntero a la Entity hija.</returns>
	FORGE_API Entity* addChild(Entity* child);
	/// <summary>
	/// Elimina de los hijos a la Entity pasada
	/// </summary>
	/// <param name="child">Entity que se quiere eliminar de la lista de hijos</param>
	/// <returns>Puntero a la Entity eliminada</returns>
	FORGE_API Entity* removeChild(Entity* child);
	/// <summary>
	/// Elimina el Component dicho de la Entity
	/// </summary>
	/// <param name="id">Id del Component a eliminar</param>
	FORGE_API void removeComponent(std::string const& id);
	/// <summary>
	/// Elimina el Component dicho de la Entity
	/// </summary>
	/// <typeparam name="ComponentType">Tipo del Component a eliminar</typeparam>
	template<class ComponentType>
	FORGE_API inline void removeComponent() {
		removeComponent(ComponentType::Id());
	}
	/// <summary>
	/// Devuelve un puntero al componente pedido de la Entity
	/// </summary>
	/// <typeparam name="ComponentType">Tipo del Component a acceder</typeparam>
	/// <returns> Un puntero al Component pedido de esta Entity. nullptr si no lo tiene</returns>
	template<class ComponentType>
	FORGE_API inline ComponentType* getComponent() {
		auto comp = componentMap.find(ComponentType::id);
		if (comp == componentMap.end()) {
			return nullptr;
		}
		return static_cast<ComponentType*>(comp->second);
	}
	/// <summary>
	/// Comprueba si la Entity tiene el Component indicado
	/// </summary>
	/// <param name="name">Nombre del Component a consultar</param>
	/// <returns>Booleano que indica si la Entity tiene el Component</returns>
	FORGE_API bool hasComponent(std::string const& name);
	/// <summary>
	/// Comprueba si la Entity tiene el Component indicado
	/// </summary>
	/// <typeparam name="ComponentType">Tipo de Component a consultar</typeparam>
	/// <returns>Booleano que indica si la Entity tiene el Component</returns>
	template<class ComponentType>
	FORGE_API inline bool hasComponent() {
		return hasComponent(ComponentType::id);
	}
	/// <returns>
	/// El grupo al que pertenece la Entity
	/// </returns>
	FORGE_API int getGroup();
	/// <returns>
	/// Un unordered_set con punteros a los hijos de la entidad
	/// </returns>
	FORGE_API const std::unordered_set<Entity*>& getChildren() const;
	/// <summary>
	/// Actualiza la logica de la Entity
	/// </summary>
	FORGE_API void update();
	/// <summary>
	///	Actualiza la Entity en periodos de tiempo fijos
	/// </summary>
	FORGE_API void fixedUpdate();
	/// <summary>
	/// Establece si todos los Components de la Entity estan activados
	/// </summary>
	/// <param name="_enabled">Nuevo estado de activacion de los Components</param>
	FORGE_API void setEnabled(bool enabled);
	/// <returns>
	/// Booleano que indica si la Entity se mantiene entre escenas
	/// </returns>
	FORGE_API bool isKeepBetweenScenes();
	/// <summary>
	/// Asigna si la Entity se mantiene entre escenas al realizar un cambio de escena
	/// </summary>
	/// <param name="keep">Valor para indicar si se mantiene la Entity</param>
	FORGE_API void setKeepBetweenScenes(bool keep);
	/// <summary>
	/// Cambia la Scene en la que se encuentra esta Entity
	/// </summary>
	/// <param name="newScene">Puntero a la nueva Scene</param>
	FORGE_API void changeScene(Scene* newScene);
	/// <summary>
	/// Devuelve una referencia al invocador de la entidad
	/// </summary>
	/// <returns>Referencia al invocador de la entidad</returns>
	FORGE_API Invoker& getInvoker();
};
#endif
