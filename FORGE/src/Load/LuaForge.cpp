#include "LuaForge.h"
#include <lua.hpp>
#include <LuaBridge/LuaBridge.h>
void LuaForge::initializeClassesToLua() {
	luabridge::getGlobalNamespace(lua).beginClass<LuaForge>("e").addConstructor<void>()
}

LuaForge::LuaForge() :
	lua(luaL_newstate()) {
	luaL_openlibs(lua);
	initializeClassesToLua();
}

LuaForge::~LuaForge() {
	lua_close(lua);
}

lua_State* LuaForge::getState() const {
	return lua;
}

void LuaForge::dofile(std::string path) {
	luaL_dofile(lua, path.c_str());
}
