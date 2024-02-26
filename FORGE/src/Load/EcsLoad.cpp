#include "EcsLoad.h"
#include <lua.hpp>
#include <LuaBridge/LuaBridge.h>
#include "EntityData.h"
#include "SceneManager.h"

EcsLoad::EcsLoad(std::string path) : 
	filePath(path),
	sceneManager(*SceneManager::getInstance()) {
	using namespace luabridge;

	lua = luaL_newstate();
	luaL_dofile(lua, path.c_str());

	LuaRef entityBlueprints = LuaRef::fromStack(lua, 1);
	LuaRef sceneBlueprints = LuaRef::fromStack(lua, 2);

	for (auto&& entity : pairs(entityBlueprints)) {
		EntityData* blueprint = parseEntityStruct(entity.second);
		blueprint->isBlueprint = true;
		sceneManager.addEntityBlueprint(entity.first.cast<std::string>(), blueprint);
	}

	for (auto&& scene : pairs(sceneBlueprints)) {
		sceneManager.addSceneBlueprint(scene.first.cast<std::string>(), parseScene(scene.second));
	}
}

void EcsLoad::extractEntityValues(EntityData& es, luabridge::LuaRef& h, luabridge::LuaRef& g, luabridge::LuaRef& cmps) {
	if (!h.isNil()) {
		es.handler = h.cast<std::string>();
	}
	if (!g.isNil()) {
		es.group = g.cast<std::string>();
	}
	if (!cmps.isNil()) {
		for (auto&& cmp : pairs(cmps)) {
			// Crear copias de los LuaRef para no perder las referencias de los datos en la pila
			es.components[cmp.first.cast<std::string>()] = new luabridge::LuaRef(cmp.second);
		}
	}
}

EntityData* EcsLoad::parseEntityStruct(luabridge::LuaRef& l_entity) {
	luabridge::LuaRef
		group = l_entity["group"],
		handler = l_entity["handler"],
		blueprint = l_entity["blueprint"],
		components = l_entity["components"];

	EntityData* es;
	if (blueprint.isNil()) {
		es = new EntityData();
		extractEntityValues(*es, handler, group, components);
	}
	else {
		es = sceneManager.getEntityBlueprint(blueprint.cast<std::string>());
		if (!(handler.isNil() && group.isNil() && components.isNil())) {
			es = new EntityData(*es);
			es->isBlueprint = false;
			extractEntityValues(*es, handler, group, components);
		}
	}

	return es;
}

std::vector<EntityData*> EcsLoad::parseScene(luabridge::LuaRef& l_scene) {
	std::vector<EntityData*> scene;
	for (auto&& entity : pairs(l_scene)) {
		scene.push_back(parseEntityStruct(entity.second));
	}
	return scene;
}
