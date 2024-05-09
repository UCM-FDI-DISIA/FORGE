#pragma once
#ifndef INVOKER_H_
#define INVOKER_H_

#include <string>
#include <functional>
#include <unordered_map>
#include "ForgeExport.h"

/// <summary>
/// Invocador, sirve para registrar funciones de C++ y llamarlas desde Lua a traves de el
/// </summary>
class Invoker {
private:
	std::unordered_map<std::string, std::function<void()>>& functions;
	bool valid;
public:
	/// <summary>
	/// Invocador, sirve para registrar funciones de C++ y llamarlas desde Lua a traves de el
	/// </summary>
	FORGE_API Invoker();
	/// <summary>
	/// Guarda el registro de una funcion de C++ que se quiere llamar desde Lua
	/// </summary>
	/// <param name="name">Nombre con el que se accedera a la funcion desde Lua</param>
	/// <param name="f">Funcion que se llamara en la invocacion</param>
	FORGE_API void registerFunction(std::string const& name, std::function<void()> const& f);
	/// <summary>
	/// Llama, si existe, a la funcion registrada con el nombre introducido
	/// </summary>
	/// <param name="func">Nombre de la funcion registrada que se quiere invocar</param>
	FORGE_API void invoke(std::string const& func);
	/// <summary>
	/// Invalida el Invoker
	/// </summary>
	FORGE_API void invalidate();
};


#endif // !INVOKER_H_
