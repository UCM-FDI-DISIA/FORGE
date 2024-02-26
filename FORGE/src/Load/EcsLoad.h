#pragma once
#ifndef ECS_LOAD_H_
#define ECS_LOAD_H_
#include <string>
#include <vector>
#include <unordered_map>

struct lua_State;
class SceneManager;
namespace luabridge {
	class LuaRef;
}
struct EntityData;

class EcsLoad {
private:
	lua_State* lua;
	std::string filePath;
	SceneManager& sceneManager;
public:
	EcsLoad(std::string path);
	void extractEntityValues(EntityData& es, luabridge::LuaRef& h, luabridge::LuaRef& g, luabridge::LuaRef& cmps);
	EntityData* parseEntityStruct(luabridge::LuaRef& data);
	std::vector<EntityData*> parseScene(luabridge::LuaRef& data);
};

#endif // !ECS_LOAD_H_