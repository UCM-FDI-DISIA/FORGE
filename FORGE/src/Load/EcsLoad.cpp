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

void EcsLoad::extractChildren(EntityData& ed, luabridge::LuaRef& children) {
	if (!children.isNil()) {
		if (!ed.isBlueprint) {
			for (auto&& child : pairs(children)) {
				ed.children.push_back(parseEntityData(child.second));
			}
		}
		else {
			for (auto&& child : pairs(children)) {
				luabridge::LuaRef index = child.second["index"];
				if (index.isNil()) {
					ed.children.push_back(parseEntityData(child.second));
				}
				else {
					int i = index[0].cast<int>();
					if (i < 0 || i >= ed.children.size()) {
						ed.children.push_back(parseEntityData(child.second));
					}
					else {
						std::string mode = index[1].cast<std::string>();
						EntityData*& edChild = ed.children[i];
						if (mode == "modify") {
							// si estas modificando un blueprint lo copias
							if (edChild->isBlueprint) {
								edChild = new EntityData(*edChild);
							}
							modifyChildrenData(*edChild, child.second);
						}
						else {
							if (edChild && !edChild->isBlueprint) {
								delete edChild;
							}
							edChild = nullptr;
							if (mode != "delete"/*|| (mode == "replace")*/) {
								edChild = parseEntityData(child.second);
							}
						}
					}
				}
			}
		}
	}

}

void EcsLoad::modifyChildrenData(EntityData& cd, luabridge::LuaRef& data) {
	luabridge::LuaRef
		group = data["group"],
		handler = data["handler"],
		components = data["components"],
		children = data["children"];
	extractEntityValues(cd, handler, group, components);
	cd.isBlueprint = true;
	extractChildren(cd, children);
	cd.isBlueprint = false;
}


EntityData* EcsLoad::parseEntityData(luabridge::LuaRef& l_entity) {
	luabridge::LuaRef
		group = l_entity["group"],
		handler = l_entity["handler"],
		blueprint = l_entity["blueprint"],
		components = l_entity["components"],
		children = l_entity["children"];


	EntityData* es;
	if (blueprint.isNil()) {
		es = new EntityData();
		extractEntityValues(*es, handler, group, components);
		extractChildren(*es, children);
	}
	else {
		es = sceneManager.getEntityBlueprint(blueprint.cast<std::string>());
		if (!(handler.isNil() && group.isNil() && components.isNil() && children.isNil())) {
			es = new EntityData(*es);
			extractEntityValues(*es, handler, group, components);
			extractChildren(*es, children);
			es->isBlueprint = false;
		}
	}

	return es;
}

std::vector<EntityData*> EcsLoad::parseScene(luabridge::LuaRef& l_scene) {
	std::vector<EntityData*> scene;
	for (auto&& entity : pairs(l_scene)) {
		scene.push_back(parseEntityData(entity.second));
	}
	return scene;
}
