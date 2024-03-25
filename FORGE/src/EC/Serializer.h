#pragma once
#ifndef SERIALIZER_H_
#define SERIALIZER_H_

#include <string>
#include <vector>
#include "Component.h"
#include "ComponentData.h"
#include <type_traits>


/// <summary>
/// Clase interna que se encarga de almacenar e inicializar todas las variables que se quieran serializar de un Component desde un archivo Lua o un ComponentData.
/// </summary>
class Component::Serializer {
private:
	/// <summary>
	/// Interfaz interna que almacena el nombre de una variable que se va a serializar.
	/// </summary>
	class BaseSerialized {
	protected:
		std::string name;
	public:
		/// <summary>
		/// Constructor de BaseSerialized, almacena el nombre dentro de Lua o ComponentData de la variable que inicializara.
		/// </summary>
		/// <param name="myName">Nombre que se le dara a la variable dentro de Lua o ComponentData.</param>
		BaseSerialized(std::string myName);
		/// <summary>
		/// Asigna a la variable serializada el valor que tenga dentro del ComponentData.
		/// </summary>
		/// <param name="data">ComponentData dentro del que esta la informacion de la variable serializada.</param>
		virtual void initialize(ComponentData& data) = 0;
	};


	/// <summary>
	/// Clase plantilla interna que almacena e inicializa una variable serializada en Lua o ComponentData.
	/// </summary>
	/// <typeparam name="T">Tipo de la variable a inicializar. Casteable de Lua a C++ a traves de LuaBridge.</typeparam>
	template <typename T>
	class Serialized : public BaseSerialized {
		T& var;
	public:
		/// <summary>
		/// Constructor de Serialized, almacena la referencia a la variable que inicializara y su nombre en Lua o ComponentData.
		/// </summary>
		/// <param name="myVar">Variable que se va a inicializar.</param>
		/// <param name="myName">Nombre de la variable dentro del archivo Lua o del ComponentData.</param>
		inline Serialized(T& myVar, std::string myName) :
			BaseSerialized(myName),
			var(myVar) {
		}
		/// <summary>
		/// Asigna a la variable serializada el valor que tenga dentro del LuaRef o ComponentData.
		/// </summary>
		/// <param name="data">ComponentData dentro del que esta la informacion de la variable serializada.</param>
		void initialize(ComponentData& data) override {
			if (data.has(name)) {
				var = data.get<T>(name);
				handle_initialize<T>(var);
			}
		}
		/// <summary>
		/// Comprueba posibles errores en la inicializacion de las variables.
		/// </summary>
		/// <typeparam name="U">Tipo de la variable</typeparam>
		/// <param name="var">La variable casteada que se va a comprobar</param>
		template<typename U>
		void handle_initialize(U& var) {
		}

		template<>
		void handle_initialize(float& var) {
			if (std::isinf(var)) {
				std::cerr << "ERROR: Variable " << name << " con valor infinito. Seteado a 0" << std::endl;
				var = 0.0f;
			}
		}
	};

	std::vector<BaseSerialized*> serializations;
public:
	/// <summary>
	/// Agrega una nueva variable a serializar.
	/// </summary>
	/// <typeparam name="T">Tipo casteable de Lua a C++ a traves de LuaBridge.</typeparam>
	/// <param name="var">Referencia a la variable en la que se querran cargar los datos del archivo Lua o del ComponentData.</param>
	/// <param name="name">Nombre que recibira el valor a guardar dentro del archivo Lua.</param>
	/// <example>
	/// Ejemplo de uso dentro de un Component (C++)
	/// <code>
	/// class MiComponente : public Component {
	///		int cantidad;
	///		MiComponente() {
	///			serializer.addField(cantidad, "cantidad");
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
	inline void addField(T& var, std::string name) {
		serializations.push_back(new Serialized<T>(var, name));
	}
	/// <summary>
	/// Agrega una nueva variable a serializar.
	/// </summary>
	/// <typeparam name="T">Tipo casteable de Lua a C++ a traves de LuaBridge.</typeparam>
	/// <param name="var">Referencia a la variable en la que se querran cargar los datos del archivo Lua o del ComponentData.</param>
	/// <param name="name">Nombre que recibira el valor a guardar dentro del archivo Lua.</param>
	/// <example>
	/// Ejemplo de uso dentro de un Component (C++)
	/// <code>
	/// class MiComponente : public Component {
	///		int cantidad;
	///		MiComponente() {
	///			serializer(cantidad, "cantidad");
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
	inline void operator()(T& var, std::string name) {
		addField<T>(var, name);
	}
	/// <summary>
	/// Llamado desde el constructor del Component, guarda un valor que se quiere cargar de forma externa
	/// a traves de un archivo Lua o un ComponentData.
	/// </summary>
	/// <param name="data">ComponentData dentro del que se encuentra la informacion de las variables serializadas.</param>
	void initialize(ComponentData& data);
	template<typename U>
	void handle_initialize(U& var);
	template<>
	void handle_initialize<float>(float& var);	
	/// <summary>
	/// Destructor del Serializer, elimina todos los registros de campos a serializar.
	/// </summary>
	~Serializer();

};


#endif // !SERIALIZER_H_

