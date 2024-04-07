#pragma once
#ifndef COMPONENT_H_
#define COMPONENT_H_

#include <string>
#include <vector>

class Entity;
class Scene;
class ComponentData;

class Component {
private:
	class Serializer;
	bool enabled;

protected:
	Serializer& serializer;
	Entity* entity;
	Scene* scene;

public:
	/// <summary>
	/// Constructora por defecto de la clase Component
	/// </summary>	
	Component();
	/// <summary>
	/// Destructora por defecto de la clase Component
	/// </summary>	
	virtual ~Component();
	/// <summary>
	/// Establece la Entity a la que pertenece este Component y la Scene a la que pertenece la Entity
	/// </summary>
	/// <param name="_entity">Entity a la que pertenece este Component</param>
	/// <param name="_scene">Scene a la que pertenece la Entity</param>
	void setContext(Entity* _entity, Scene* _scene);
	/// <summary>
	/// Inicializa los parametros serializados del Component
	/// </summary>
	/// <param name="data"> Parametros necesarios para la iniciacion del componente</param>
	bool initSerialized(ComponentData* data);
	/// <summary>
	/// Inicializa el Component con los parametros adecuados
	/// </summary>
	/// <param name="data"> Parametros necesarios para la iniciacion del componente</param>
	virtual bool initComponent(ComponentData* data);
	/// <summary>
	/// Actualiza la logica del Component
	/// </summary>
	virtual void update();
	/// <summary>
	///	Actualiza el Component en periodos de tiempo fijos
	/// </summary>
	virtual void fixedUpdate();
	/// <summary>
	///	Establece si el componente esta activado
	/// </summary>
	/// <param name="_enabled">Nuevo estado de activacion del Component</param>
	virtual void setEnabled(bool _enabled);

	/// <summary>
	/// Metodo que se llama cada vez que se activa el componente
	/// </summary>
	virtual void onEnabled();
	/// <summary>
	/// Metodo que se llama cada vez que se desactiva el componente
	/// </summary>
	virtual void onDisabled();

	#pragma region Getters
	/// <returns>
	///	Si el Component esta activado
	/// </returns>
	bool isEnabled() const;
	/// <returns>
	///	La Entity a la que pertenece el Component
	/// </returns>
	Entity* getEntity() const;
	/// <returns>
	///	La Scene a la que pertenece la Entity padre
	/// </returns>
	Scene* getScene() const;
	#pragma endregion
};

#endif // !COMPONENT_H_

