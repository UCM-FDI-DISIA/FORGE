#pragma once
#ifndef FORGE_FUNCTION_H_
#define FORGE_FUNCTION_H_

#include <lua.hpp>
#pragma warning(push)
#pragma warning(disable : 26439)
#include <LuaBridge/LuaBridge.h>
#pragma warning(pop)
#include "Invoker.h"

template <typename T>
class ForgeFunction {
private:
	luabridge::LuaRef functionRef;

public:
	/// <summary>
	/// Constructora por defecto de ForgeFunction
	/// </summary>
	inline ForgeFunction(luabridge::LuaRef const& funcRef) :
		functionRef(funcRef) {
	}
	/// <summary>
	/// Llamada a la funcion
	/// </summary>
	/// <returns>Valor devuelto por la funcion</returns>
	inline T invoke(Invoker const& invoker) {
		if (functionRef.isFunction()) {
			luabridge::LuaRef ret = functionRef(invoker);
			if (ret.isInstance<T>()) {
				return ret.cast<T>();
			}
		}
		return T();
	}
	/// <summary>
	/// Llamada a la funcion
	/// </summary>
	/// <returns>Valor devuelto por la funcion</returns>
	inline T operator()(Invoker const& invoker) {
		return invoke(invoker);
	}
};

template <>
class ForgeFunction<void> {
private:
	luabridge::LuaRef functionRef;

public:
	/// <summary>
	/// Constructora por defecto de ForgeFunction
	/// </summary>
	inline ForgeFunction(luabridge::LuaRef const& funcRef) :
		functionRef(funcRef) {
	}
	/// <summary>
	/// Llamada a la funcion si era una
	/// </summary>
	inline void invoke(Invoker const& invoker) {
		if (functionRef.isFunction()) {
			luabridge::LuaRef ret = functionRef(invoker);
		}
	}
	/// <summary>
	/// Llamada a la funcion
	/// </summary>
	/// <returns>Valor devuelto por la funcion</returns>
	inline void operator()(Invoker const& invoker) {
		invoke(invoker);
	}
};

#endif // !FORGE_FUNCTION_H_