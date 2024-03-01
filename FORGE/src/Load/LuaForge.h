#pragma once
#ifndef LUA_FORGE_H_
#define LUA_FORGE_H_

#include <string>
#include <vector>
#include <functional>
struct lua_State;

class LuaForge {
private:
	lua_State* lua;
	std::vector<std::function<void(lua_State*)>> userClassesToImport;
	/// <summary>
	/// Se encarga de crear en Lua todas las clases esenciales que se vayan a usar dentro de los archivos a leer
	/// </summary>
	void importForgeClassesToLua();
	/// <summary>
	/// Llama a todas las funciones de creacion de clases que haya creado el usuario
	/// </summary>
	void importUserClassesToLua();
public:
	/// <summary>
	/// Constructor, crea un lua_State, abre las libs e importa a Lua las clases queridas de FORGE y las pedidas por el usuario
	/// </summary>
	LuaForge();
	/// <summary>
	/// Elimina su lua_State
	/// </summary>
	~LuaForge();
	/// <summary>
	/// Devuelve el lua_State contenido
	/// </summary>
	/// <returns>Un puntero al lua_State contenido en la clase</returns>
	lua_State* getState() const;
	/// <summary>
	/// Llama a lua_dofile para el  lua_State contenido
	/// </summary>
	/// <param name="path">Ruta del archivo .lua que se quiere ejecutar</param>
	void dofile(std::string path);
	/// <summary>
	/// Permite agregar una clase propia al lua_State contenido a través de LuaBridge
	/// </summary>
	/// <param name="classCreation">Funcion que recibe lua_State* y que agrega una clase al lua_State recibido</param>
	/// <example>
	/// Ejemplo:
	/// <code>
	/// auto classCreation = [](lua_State* L) {
	///		luabridge::getGlobalNamespace(L)
	///			.beginClass<Vector3>("Vector3")
	///				.addConstructor<void(*)(double, double, double)>()
	///			.endClass();
	/// };
	/// importClassToLua(classCreation);
	/// </code>
	/// </example>
	void importClassToLua(std::function<void(lua_State*)> classCreation);
};

#endif // !LUA_FORGE_H_