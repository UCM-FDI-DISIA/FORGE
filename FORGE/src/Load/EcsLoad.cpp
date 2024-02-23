#include "EcsLoad.h"
#include <lua.hpp>
#include <LuaBridge/LuaBridge.h>
#include "../EC/SceneManager.h"

EcsLoad::EcsLoad(std::string path) : 
	filePath(path) {
	lua = luaL_newstate();
	using namespace luabridge;
	LuaRef lr = LuaRef::fromStack(lua, -1);
	SceneManager& sm = *SceneManager::getInstance();
	for (luabridge::Iterator it(lr); !it.isNil(); ++it) {
		sm.addEntityBlueprint(it.key().cast<std::string>(), parseEntityStruct(it.value()));
	}

	lr = LuaRef::fromStack(lua, -2);
	for (luabridge::Iterator it(lr); !it.isNil(); ++it) {
		sm.addSceneBlueprint(it.key().cast<std::string>(), parseScene(it.value()));
	}
}

EntityStruct EcsLoad::parseEntityStruct(luabridge::LuaRef data) {
	EntityStruct es;
	es.handler = data["handler"].cast<std::string>();
	es.group = data["group"].cast<std::string>();
	luabridge::LuaRef comps = data["components"];

	for (luabridge::Iterator it(comps); !it.isNil(); ++it) {
		es.components.insert({ it.key().cast<std::string>(), it.value() });
	}
	
	return es;
}

std::vector<EntityStruct*> EcsLoad::parseScene(luabridge::LuaRef data) {
	std::vector<EntityStruct*> sc;
	for (luabridge::Iterator it(data); !it.isNil(); ++it) {
		if (it.value()["blueprint"].isNil()) {
			sc.push_back(new EntityStruct(parseEntityStruct(it.value())));
		}
		else {

			for (luabridge::Iterator it(comps); !it.isNil(); ++it) {
				es.components.insert({ it.key().cast<std::string>(), it.value() });
			}

		}
	}
}