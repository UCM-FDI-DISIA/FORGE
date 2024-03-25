#include "LuaForge.h"
#include <lua.hpp>
#pragma warning(push)
#pragma warning(disable : 26439)
#include <LuaBridge/LuaBridge.h>
#pragma warning(pop)
#include "Vector2.h"
#include "Vector3.h"
#include "Quaternion.h"

void LuaForge::importForgeClassesToLua() {
	luabridge::getGlobalNamespace(lua)
		.beginClass<forge::Vector2>("Vector2")
			.addConstructor<void(*)(double, double)>()
		.endClass()
		.beginClass<forge::Vector3>("Vector3")
			.addConstructor<void(*)(double, double, double)>()
		.endClass()
		.beginClass<forge::Quaternion>("Quaternion")
			.addConstructor<void(*)(double, double, double, double)>()
		.endClass()
	;
}

void LuaForge::importUserClassesToLua() {
	for (auto& importCallback : userClassesToImport) {
		importCallback(lua);
	}
}

LuaForge::LuaForge() :
	lua(luaL_newstate()) {
	luaL_openlibs(lua);
	importForgeClassesToLua();
	importUserClassesToLua();
}

lua_State* LuaForge::getState() const {
	return lua;
}

void LuaForge::doFile(std::string path) {
	luaL_dofile(lua, path.c_str());
}

void LuaForge::importClassToLua(std::function<void(lua_State*)> classCreation) {
	userClassesToImport.push_back(classCreation);
}
