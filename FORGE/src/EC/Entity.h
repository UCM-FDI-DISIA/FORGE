#pragma once
#ifndef ENTITY_H_
#define ENTITY_H_
#include <unordered_map>
#include <string>

class Scene;
class Component;
class Entity;
struct Group {
	std::string id;
	std::vector<Entity> entities;
};

class Entity {
private:
	Scene* scene;
	std::unordered_map<std::string, Component*> components;
	Group group;
	bool alive;
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
	void setContext(Scene* _scene, Group _group);
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
	/// Agrega el Component dicho a la Entity, devuelve un puntero a ese Component
	/// </summary>
	/// <returns>El Component agregado</returns>
	/// <param name="data">Informacion del componente en formato de object de Lua</param>
	Component* addComponent(/*LuaObject data*/);
	/// <summary>
	/// Elimina el Component dicho de la Entity
	/// </summary>
	/// <param name="name">Nombre del Component a eliminar</param>
	void removeComponent(std::string name);
	/// <returns>
	/// El Component pedido de esta Entity
	/// </retuns>
	template<typename T>
	inline T* getComponent() {
		return static_cast<T*>(components.at(T::id));
	}
	/// <returns>
	/// Si la Entity tiene el Component pedido
	/// </returns>
	bool hasComponent(std::string name);
	/// <returns>
	/// El grupo al que pertenece la Entity
	/// </returns>
	Group getGroup();
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
