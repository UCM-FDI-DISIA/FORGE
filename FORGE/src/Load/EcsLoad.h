#pragma once
#ifndef ECS_LOAD_H_
#define ECS_LOAD_H_
#include <string>
#include <vector>
#include <unordered_map>

class lua_State;
class SceneManager;
namespace luabridge {
	class LuaRef;
}

struct EntityStruct {
	std::string group;
	std::string handler;
	std::unordered_map<std::string, luabridge::LuaRef> components;
};

class EcsLoad {
private:
	lua_State* lua;
	std::string filePath;
	SceneManager* sceneManager;
public:
	EcsLoad(std::string path);
	EntityStruct parseEntityStruct(luabridge::LuaRef data, EntityStruct bp = EntityStruct());
	std::vector<EntityStruct*> parseScene(luabridge::LuaRef data);
};

#endif // !ECS_LOAD_H_