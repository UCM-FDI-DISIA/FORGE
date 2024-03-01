#pragma once
#ifndef LUA_FORGE_H_
#define LUA_FORGE_H_

#include <string>
#include <vector>
struct lua_State;

class LuaForge {
private:
	lua_State* lua;
	void initializeClassesToLua();
public:
	LuaForge();
	~LuaForge();
	lua_State* getState() const;
	void dofile( std::string path );
};

#endif // !LUA_FORGE_H_