#pragma once
#ifndef COMPONENT_H_
#define COMPONENT_H_

#include <string>
#include <vector>

class Entity;
class Scene;
namespace luabridge {
	class LuaRef;
}

class Component {
private:
	/// <summary>
	/// Interfaz interna que almacena el nombre de una variable que se va a serializar
	/// </summary>
	class BaseSerialized {
	protected:
		std::string name;
	public:
		/// <summary>
		/// Constructor de BaseSerialized, almacena el nombre dentro de Lua de la variable que inicializará
		/// </summary>
		/// <param name="myName"></param>
		BaseSerialized(std::string myName);
		/// <summary>
		/// Asigna a la variable serializada el valor que tenga dentro del LuaRef
		/// </summary>
		/// <param name="data">LuaRef dentro del que está la información de la variable serializada</param>
		virtual void initialize(luabridge::LuaRef& data) = 0;
	};
	/// <summary>
	/// Clase plantilla interna que almacena e inicializa una variable serializada en Lua
	/// </summary>
	/// <typeparam name="T">Tipo de la variable a inicializar. Casteable de Lua a C++ a traves de LuaBridge</typeparam>
	template <typename T>
	class Serialized : public BaseSerialized {
		T& var;
	public:
		/// <summary>
		/// Constructor de Serialized, almacena la referencia a la variable que inicializara y su nombre en Lua
		/// </summary>
		/// <param name="myVar">Variable que se va a inicializar</param>
		/// <param name="myName">Nombre de la variable dentro del archivo Lua</param>
		inline Serialized(T& myVar, std::string myName) :
			BaseSerialized(myName),
			var(myVar) {
		}
		/// <summary>
		/// Asigna a la variable serializada el valor que tenga dentro del LuaRef
		/// </summary>
		/// <param name="data">LuaRef dentro del que esta la informacion de la variable serializada</param>
		void initialize(luabridge::LuaRef& data) override;
	};
	/// <summary>
	/// Clase interna que se encarga de almacenar e inicializar todas las variables que se quieran serializar desde un archivo Lua
	/// </summary>
	class Serializer : private std::vector<BaseSerialized*> {
	public:
		/// <summary>
		/// Agrega una nueva variable a serializar
		/// </summary>
		/// <typeparam name="T">Tipo casteable de Lua a C++ a traves de LuaBridge.</typeparam>
		/// <param name="var">Referencia a la variable en la que se querran cargar los datos del archivo Lua.</param>
		/// <param name="name">Nombre que recibira el valor a guardar dentro del archivo Lua.</param>
		template <typename T>
		inline void addField(T& var, std::string name) {
			push_back(new Serialized(var, name));
		}
		/// <summary>
		/// Asigna a las variables guardadas para serializar el valor que tengan dentro del LuaRef pasado
		/// </summary>
		/// <param name="data">LuaRef dentro del que se encuentra la información de las variables serializadas</param>
		void initialize(luabridge::LuaRef& data);
		/// <summary>
		/// Destructor del Serializer, elimina todos los registros de campos a serializar
		/// </summary>
		~Serializer();
	};


	Serializer ser;

protected:
	Entity* entity;
	Scene* scene;

	bool enabled;

	/// <summary>
	/// Llamado desde el constructor del Component, guarda un valor que se quiere cargar de forma externa
	/// a traves de un archivo Lua.
	/// </summary>
	/// <typeparam name="T">Tipo casteable de Lua a C++ a traves de LuaBridge.</typeparam>
	/// <param name="var">Referencia a la variable en la que se querran cargar los datos del archivo Lua.</param>
	/// <param name="name">Nombre que recibira el valor a guardar dentro del archivo Lua.</param>
	/// <example>
	/// Ejemplo de uso dentro de un Component (C++)
	/// <code>
	/// class MiComponente : public Component {
	///		int cantidad;
	///		MiComponente() {
	///			SerializeField(cantidad, "cantidad");
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
	template <typename T>
	inline void SerializeField(T& var, std::string name) {
		ser.addField(var, name);
	}
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
	/// Inicializa el Component con los parametros adecuados
	/// </summary>
	/// <param name="data"> Parametros necesarios para la iniciacion del componente</param>
	virtual void initComponent(luabridge::LuaRef* data);
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
};

#endif // !COMPONENT_H_

