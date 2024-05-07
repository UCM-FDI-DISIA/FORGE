#pragma once
#ifndef LUA_FORGE_H_
#define LUA_FORGE_H_

#include <string>
#include <vector>
#include <functional>
#include "ForgeExport.h"
struct lua_State;
namespace luabridge {
	class LuaRef;
}

class LuaForge {
private:
	lua_State* lua;
	/// <summary>
	/// Se encarga de crear en Lua todas las clases esenciales que se vayan a usar dentro de los archivos a leer
	/// </summary>
	void importForgeClassesToLua();
public:
	/// <summary>
	/// Constructor, crea un lua_State, abre las libs e importa a Lua las clases queridas de FORGE y las pedidas por el usuario
	/// </summary>
	LuaForge();
	/// <summary>
	/// Vacia la pila de lua
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
	bool doFile(std::string const& path);
};

#endif // !LUA_FORGE_H_