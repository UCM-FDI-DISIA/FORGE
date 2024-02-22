#pragma once
#ifndef ECS_LOAD_H_
#define ECS_LOAD_H_
#include <string>
#include <vector>

namespace luabridge {
	class LuaRef;
}

struct ComponentStruct {
	std::string id;
	luabridge::LuaRef* data;
};

struct EntityStruct {
	std::string group;
	std::string handler;
	std::vector<ComponentStruct*> components;
};

class EcsLoad {
private:
	lua_State* lua;
	std::string filePath;
public:
	EcsLoad(std::string path);
};

#endif // !ECS_LOAD_H_