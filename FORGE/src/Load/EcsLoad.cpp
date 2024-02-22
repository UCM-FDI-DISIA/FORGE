#include "EcsLoad.h"
#include <lua.hpp>
#include <LuaBridge/LuaBridge.h>

EcsLoad::EcsLoad(std::string path) : 
	filePath(path) {
	lua = luaL_newstate();
}
