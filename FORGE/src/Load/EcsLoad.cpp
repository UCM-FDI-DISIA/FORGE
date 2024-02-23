#include "EcsLoad.h"
#include <lua.hpp>
#include <LuaBridge/LuaBridge.h>
#include "../EC/SceneManager.h"

EcsLoad::EcsLoad(std::string path) : 
	filePath(path),
	sceneManager(*SceneManager::getInstance()) {
	using namespace luabridge;

	lua = luaL_newstate();
	luaL_dofile(lua, path.c_str());

	LuaRef lr = LuaRef::fromStack(lua, 1);
	for (auto&& pair : pairs(lr)) {
		sceneManager.addEntityBlueprint(pair.first.cast<std::string>(), parseEntityStruct(pair.second));
	}

	lr = LuaRef::fromStack(lua, 1);
	for (auto&& pair : pairs(lr)) {
		sceneManager.addSceneBlueprint(pair.first.cast<std::string>(), parseScene(pair.second));
	}
}

EntityStruct EcsLoad::parseEntityStruct(luabridge::LuaRef data, EntityStruct bp) {
	EntityStruct es(bp);
	es.handler = data["handler"].cast<std::string>();
	es.group = data["group"].cast<std::string>();
	luabridge::LuaRef comps = data["components"];
	for (auto&& pair : pairs(comps)) {
		auto k = pair.first.cast<std::string>();
		es.components[k] = &(pair.second);
	}
	
	return es;
}

std::vector<EntityStruct*> EcsLoad::parseScene(luabridge::LuaRef data) {
	std::vector<EntityStruct*> scene;
	for (auto&& pair : pairs(data)) {
		if (pair.second["blueprint"].isNil()) {
			scene.push_back(new EntityStruct(parseEntityStruct(pair.second)));
		}
		else {
			EntityStruct bp = sceneManager.getEntityBlueprint(it.value()["blueprint"]);
			if (pair.second["components"].isNil() && pair.second["handler"].isNil() && pair.second["group"].isNil()) {
				scene.push_back(&bp);
			}
			else {
				scene.push_back(new EntityStruct(parseEntityStruct(pair.second, bp)));
			}
		}
	}
	return scene;
}