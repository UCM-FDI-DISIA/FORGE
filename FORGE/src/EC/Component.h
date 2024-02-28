#pragma once
#ifndef COMPONENT_H_
#define COMPONENT_H_

#include <string>
#include <vector>

class Entity;
class Scene;
class Serializer;
class ComponentData;

class Component {
protected:
	Serializer* serializer;
	Entity* entity;
	Scene* scene;

	bool enabled;
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
	void initSerialized(ComponentData* data);
	/// <summary>
	/// Inicializa el Component con los parametros adecuados
	/// </summary>
	/// <param name="data"> Parametros necesarios para la iniciacion del componente</param>
	virtual void initComponent(ComponentData* data);
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
	void setEnabled(bool _enabled);
	/// <returns>
	///	Si el Component esta activado
	/// </returns>
	bool isEnabled();
	/// <summary>
	/// Accede al objeto del serializer en vez de al puntero y permite agregar variables a serializar de la siguiente manera:
	/// <example>
	/// Ejemplo de uso dentro de un Component (C++)
	/// <code>
	/// class MiComponente : public Component {
	///		int cantidad;
	///		MiComponente() {
	///			serialize()(cantidad, "cantidad");
	///		}
	/// };
	/// </code>
	/// Ejemplo de la informacion guardada (Lua)
	/// <code>
	/// MiComponente = {
	///		cantidad = 5
	/// }
	/// </code>
	/// </example>
	/// </summary>
	/// <returns> referencia al serilizer </returns>
	Serializer& serialize();

};

#endif // !COMPONENT_H_

