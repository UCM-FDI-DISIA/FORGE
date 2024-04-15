#pragma once
#ifndef COMPONENT_H_
#define COMPONENT_H_

#include <string>
#include <vector>
#include "ForgeExport.h"

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
	FORGE_API Component();
	/// <summary>
	/// Destructora por defecto de la clase Component
	/// </summary>	
	FORGE_API virtual ~Component();
	/// <summary>
	/// Establece la Entity a la que pertenece este Component y la Scene a la que pertenece la Entity
	/// </summary>
	/// <param name="_entity">Entity a la que pertenece este Component</param>
	/// <param name="_scene">Scene a la que pertenece la Entity</param>
	FORGE_API void setContext(Entity* _entity, Scene* _scene);
	/// <summary>
	/// Inicializa los parametros serializados del Component
	/// </summary>
	/// <param name="data">Parametros necesarios para la iniciacion del componente</param>
	FORGE_API bool initSerialized(ComponentData* data);
	/// <summary>
	/// Inicializa el Component con los parametros adecuados
	/// </summary>
	/// <param name="data">Parametros necesarios para la iniciacion del componente</param>
	FORGE_API virtual bool initComponent(ComponentData* data);
	/// <summary>
	/// Actualiza la logica del Component
	/// </summary>
	FORGE_API virtual void update(double dt);
	/// <summary>
	///	Actualiza el Component en periodos de tiempo fijos
	/// </summary>
	FORGE_API virtual void fixedUpdate();
	/// <summary>
	///	Establece si el componente esta activado
	/// </summary>
	/// <param name="_enabled">Nuevo estado de activacion del Component</param>
	FORGE_API void setEnabled(bool _enabled);
	/// <summary>
	/// Metodo que se llama cada vez que se activa el componente
	/// </summary>
	FORGE_API virtual void onEnabled();
	/// <summary>
	/// Metodo que se llama cada vez que se desactiva el componente
	/// </summary>
	FORGE_API virtual void onDisabled();
	#pragma region Getters
	/// <returns>
	///	Si el Component esta activado
	/// </returns>
	FORGE_API bool isEnabled() const;
	/// <returns>
	///	La Entity a la que pertenece el Component
	/// </returns>
	FORGE_API Entity* getEntity() const;
	/// <returns>
	///	La Scene a la que pertenece la Entity padre
	/// </returns>
	FORGE_API Scene* getScene() const;
	#pragma endregion
};

#endif // !COMPONENT_H_

