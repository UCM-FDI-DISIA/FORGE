#include "EcsLoad.h"
#include <lua.hpp>
#include <LuaBridge/LuaBridge.h>
#include "EntityData.h"
#include "ComponentData.h"
#include "SceneManager.h"
#include "LuaForge.h"

EcsLoad::EcsLoad(std::string path, LuaForge& luaForge) :
	sceneManager(*SceneManager::getInstance()) {
	using namespace luabridge;


	luaForge.dofile(path);
	lua_State* lua = luaForge.getState();
	sceneManager.setLuaState(lua);

	LuaRef entityBlueprints = LuaRef::fromStack(lua, -2);
	LuaRef sceneBlueprints = LuaRef::fromStack(lua, -1);

	for (auto&& entity : pairs(entityBlueprints)) {
		EntityData* blueprint = parseEntityData(entity.second);
		blueprint->isBlueprint = true;
		sceneManager.addEntityBlueprint(entity.first.cast<std::string>(), blueprint);
	}

	for (auto&& scene : pairs(sceneBlueprints)) {
		sceneManager.addSceneBlueprint(scene.first.cast<std::string>(), parseScene(scene.second));
	}
}

void EcsLoad::extractEntityValues(EntityData& ed, luabridge::LuaRef& h, luabridge::LuaRef& g, luabridge::LuaRef& cmps) {
	if (!h.isNil()) {
		ed.handler = h.cast<std::string>();
	}
	if (!g.isNil()) {
		ed.group = g.cast<std::string>();
		sceneManager.addGroup(ed.group);
	}
	if (!cmps.isNil()) {
		for (auto&& cmp : pairs(cmps)) {
			std::string cmpId = cmp.first.cast<std::string>();
			// Crear copias de los LuaRef para no perder las referencias de los datos en la pila
			luabridge::LuaRef* ltData = new luabridge::LuaRef(cmp.second);
			ed.components[cmpId] = new ComponentData(cmpId, ltData);
		}
	}
}

EntityData* EcsLoad::parseEntityData(luabridge::LuaRef& l_entity) {
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
		scene.push_back( parseEntityData(entity.second));
	}
	return scene;
}
