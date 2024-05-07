#include "LuaForge.h"
#include <lua.hpp>
#pragma warning(push)
#pragma warning(disable : 4244)
#pragma warning(disable : 4267)
#pragma warning(disable : 26439)
#pragma warning(disable : 26495)
#include <LuaBridge/LuaBridge.h>
#pragma warning(pop)
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Quaternion.h"
#include "Invoker.h"
#include "ForgeError.h"

void LuaForge::importForgeClassesToLua() {
	luabridge::getGlobalNamespace(lua)
		.beginClass<forge::Vector2>("Vector2")
			.addConstructor<void(*)(double, double)>()
		.endClass()
		.beginClass<forge::Vector3>("Vector3")
			.addConstructor<void(*)(double, double, double)>()
		.endClass()
		.beginClass<forge::Vector4>("Vector4")
			.addConstructor<void(*)(double, double, double, double)>()
		.endClass()
		.beginClass<forge::Quaternion>("Quaternion")
			.addConstructor<void(*)(double, double, double, double)>()
		.endClass()
		.beginClass<Invoker>("Invoker")
			.addConstructor<void(*)(void)>()
			.addFunction("invoke", &Invoker::invoke)
		.endClass();
}

LuaForge::LuaForge() :
	lua(luaL_newstate()) {
	luaL_openlibs(lua);
	importForgeClassesToLua();
}

LuaForge::~LuaForge() {
	lua_close(lua);
}

lua_State* LuaForge::getState() const {
	return lua;
}

bool LuaForge::doFile(std::string const& path) {
	bool fileNotFound = luaL_dofile(lua, path.c_str());
	if (fileNotFound) {
		reportError("Archivo " << path << " no encontrado o contiene un error de sintaxis.");
	}
	return !fileNotFound;
}