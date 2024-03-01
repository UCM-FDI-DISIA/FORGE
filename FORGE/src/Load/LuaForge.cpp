#include "LuaForge.h"
#include <lua.hpp>
#include <LuaBridge/LuaBridge.h>

void LuaForge::importForgeClassesToLua() {

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

LuaForge::~LuaForge() {
	lua_close(lua);
}

lua_State* LuaForge::getState() const {
	return lua;
}

void LuaForge::dofile(std::string path) {
	luaL_dofile(lua, path.c_str());
}

void LuaForge::importClassToLua(std::function<void(lua_State*)> classCreation) {
	userClassesToImport.push_back(classCreation);
}
