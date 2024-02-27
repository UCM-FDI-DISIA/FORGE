#pragma once
#ifndef SERIALIZER_H_
#define SERIALIZER_H_

#include <string>
#include <vector>
#include <lua.hpp>
#include <Luabridge/LuaBridge.h>

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
	void initialize(luabridge::LuaRef& data) override {
		if (!data[name].isNil()) {
			var = data[name].cast<T>();
		}
	}
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
		push_back(new Serialized<T>(var, name));
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

	template <typename T>
	void operator()(T& var, std::string name) {
		push_back(new Serialized<T>(var, name));
	}
};

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
//template <typename T>
//inline void SerializeField(T& var, std::string name) {
//	addField(var, name);
//}

#endif // !SERIALIZER_H_

