#pragma once
#ifndef ENTITY_H_
#define ENTITY_H_
#include <unordered_map>
#include <string>
#include <unordered_set>

class Scene;
class Component;
class Entity;
class Factory;
class ComponentData;

class Entity {
private:
	Factory& fact;
	Scene* scene;
	std::unordered_map<std::string, Component*> components;
	Entity* parent;
	std::unordered_set<Entity*> children;
	int groupId;
	bool alive;

	/// <summary>
	/// Establece cual es la Entity padre de esta Entity.
	/// </summary>
	/// <param name="parent">Puntero a la Entity que se establece como padre.</param>
	/// <returns>Puntero a la Entity que se establece como padre.</returns>
	Entity* setParent(Entity* parent);
public:
	/// <summary>
	/// Constructor por defecto de la clase Entity
	/// </summary>
	Entity();
	/// <summary>
	/// Destructor por defecto de la clase Entity
	/// </summary>
	virtual ~Entity();
	/// <summary>
	/// Asigna la Scene en la que esta el componente y el group al que pertenece
	/// </summary>
	/// <param name="_scene">Referencia a la escena de la Entity</param>
	/// <param name="_group">Referencia al grupo de la Entity</param>
	void setContext(Scene* _scene, int _groupId);
	/// <returns>
	/// Si la Entity esta viva
	/// </returns>
	bool isAlive();
	/// <summary>
	/// Asigna si la Entity esta viva o no, de cara al recolector de basura
	/// </summary>
	/// <param name="_alive">Nuevo estado de vida de la entidad</param>
	void setAlive(bool _alive);
	/// <summary>
	/// Agrega el Component dicho a la Entity
	/// </summary>
	/// <returns>Un puntero al Component agregado</returns>
	/// <param name="data">Identificador del componente</param>
	Component* addComponent(std::string id);
	/// <summary>
	/// Agrega el Component dicho a la Entity y lo inicializa
	/// </summary>
	/// <returns>Un puntero al Component agregado</returns>
	/// <param name="data">Informacion del componente en formato de object de Lua</param>
	Component* addComponent(ComponentData* data);
	/// <summary>
	/// Agrega una nueva Entity como hija de this, y establece this como el padre de la hija.
	/// </summary>
	/// <param name="child">Puntero a la Entity hija.</param>
	/// <returns>Puntero a la Entity hija.</returns>
	Entity* addChild(Entity* child);
	/// <summary>
	/// Elimina de los hijos a la Entity pasada
	/// </summary>
	/// <param name="child">Entity que se quiere eliminar de la lista de hijos</param>
	/// <returns>Puntero a la Entity eliminada</returns>
	Entity* removeChild(Entity* child);
	/// <summary>
	/// Elimina el Component dicho de la Entity
	/// </summary>
	/// <param name="name">Nombre del Component a eliminar</param>
	void removeComponent(std::string id);
	/// <summary>
	/// Elimina el Component dicho de la Entity
	/// </summary>
	/// <typeparam name="ComponentType">Tipo del Component a eliminar</typeparam>
	template<class ComponentType>
	inline void removeComponent() {
		removeComponent(ComponentType::id);
	}
	/// <returns>
	/// Un puntero al Component pedido de esta Entity
	/// </returns>
	template<class ComponentType>
	inline ComponentType* getComponent() {
		auto comp = components.find(ComponentType::id);
		if (comp == components.end()) {
			return nullptr;
		}
		return static_cast<ComponentType*>(comp->second);
	}
	/// <summary>
	/// Comprueba si la Entity tiene el Component indicado
	/// </summary>
	/// <param name="name">Nombre del Component a consultar</param>
	/// <returns>Booleano que indica si la Entity tiene el Component</returns>
	bool hasComponent(std::string name);
	/// <summary>
	/// Comprueba si la Entity tiene el Component indicado
	/// </summary>
	/// <typeparam name="ComponentType">Tipo de Component a consultar</typeparam>
	/// <returns>Booleano que indica si la Entity tiene el Component</returns>
	template<class ComponentType>
	bool hasComponent() {
		return hasComponent(ComponentType::id);
	}
	/// <returns>
	/// El grupo al que pertenece la Entity
	/// </returns>
	int getGroup();
	/// <summary>
	/// Actualiza la logica de la Entity
	/// </summary>
	virtual void update();
	/// <summary>
	///	Actualiza la Entity en periodos de tiempo fijos
	/// </summary>
	virtual void fixedUpdate();
};
#endif
