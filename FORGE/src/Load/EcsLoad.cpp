#include "EcsLoad.h"
#include <lua.hpp>
#include <LuaBridge/LuaBridge.h>
#include "EntityData.h"
#include "ComponentData.h"
#include "SceneManager.h"
#include "LuaForge.h"
using namespace luabridge;

EcsLoad::EcsLoad(std::string path, LuaForge& luaForge) :
	sceneManager(*SceneManager::getInstance()) {

	lua_State* lua = luaForge.getState();
	sceneManager.setLuaState(lua);

	if(!luaForge.doFile(path)) {

		LuaRef entityBlueprints = LuaRef::fromStack(lua, -2);
		LuaRef sceneBlueprints = LuaRef::fromStack(lua, -1);

		if (!entityBlueprints.isNil()) {
			for (auto&& entity : pairs(entityBlueprints)) {
				EntityData* blueprint = parseEntityData(entity.second);
				blueprint->isBlueprint = true;
				sceneManager.addEntityBlueprint(entity.first.cast<std::string>(), blueprint);
			}
		}
		if (!sceneBlueprints.isNil()) {
			for (auto&& scene : pairs(sceneBlueprints)) {
				sceneManager.addSceneBlueprint(scene.first.cast<std::string>(), parseScene(scene.second));
			}
		}
	}
}

void EcsLoad::extractEntityValues(EntityData& entityData, LuaRef& handler, LuaRef& group, LuaRef& components) {
	if (!handler.isNil()) {
		entityData.handler = handler.cast<std::string>();
	}
	if (!group.isNil()) {
		entityData.group = group.cast<std::string>();
		sceneManager.addGroup(entityData.group);
	}
	if (!components.isNil()) {
		for (auto&& component : pairs(components)) {
			std::string id = component.first.cast<std::string>();
			// Crear copias de los LuaRef para no perder las referencias de los datos en la pila
			LuaRef* data = new LuaRef(component.second);
			entityData.components[id] = new ComponentData(id, data);
		}
	}
}

void EcsLoad::extractChildren(EntityData& entityData, LuaRef& children) {
	if (!children.isNil()) {
		if (!entityData.isBlueprint) {
			for (auto&& child : pairs(children)) {
				entityData.children.push_back(parseEntityData(child.second));
			}
		}
		else {
			for (auto&& child : pairs(children)) {
				LuaRef index = child.second["index"];
				if (index.isNil()) {
					entityData.children.push_back(parseEntityData(child.second));
				}
				else {
					int i = index[0].cast<int>();
					if (i < 0 || i >= entityData.children.size()) {
						entityData.children.push_back(parseEntityData(child.second));
					}
					else {
						std::string mode = index[1].cast<std::string>();
						EntityData*& childData = entityData.children[i];
						if (mode == "modify") {
							// si estas modificando un blueprint lo copias
							if (childData->isBlueprint) {
								childData = new EntityData(*childData);
							}
							modifyChildrenData(*childData, child.second);
						}
						else {
							if (childData && !childData->isBlueprint) {
								delete childData;
							}
							childData = nullptr;
							//Modo por defecto "replace", si no se ha especificado modo o el modo es incorrecto
							if (mode != "delete") {
								childData = parseEntityData(child.second);
							}
						}
					}
				}
			}
		}
	}

}

void EcsLoad::modifyChildrenData(EntityData& childData, LuaRef& data) {
	LuaRef
		group = data["group"],
		handler = data["handler"],
		components = data["components"],
		children = data["children"];
	extractEntityValues(childData, handler, group, components);
	childData.isBlueprint = true;
	extractChildren(childData, children);
	childData.isBlueprint = false;
}


EntityData* EcsLoad::parseEntityData(LuaRef& luaEntity) {
	LuaRef
		group = luaEntity["group"],
		handler = luaEntity["handler"],
		blueprint = luaEntity["blueprint"],
		components = luaEntity["components"],
		children = luaEntity["children"];

	EntityData* entityData;
	if (blueprint.isNil()) {
		entityData = new EntityData();
		extractEntityValues(*entityData, handler, group, components);
		extractChildren(*entityData, children);
	}
	else {
		entityData = sceneManager.getEntityBlueprint(blueprint.cast<std::string>());
		if (!(handler.isNil() && group.isNil() && components.isNil() && children.isNil())) {
			entityData = new EntityData(*entityData);
			extractEntityValues(*entityData, handler, group, components);
			extractChildren(*entityData, children);
			entityData->isBlueprint = false;
		}
	}

	return entityData;
}

std::vector<EntityData*> EcsLoad::parseScene(LuaRef& luaScene) {
	std::vector<EntityData*> scene;
	for (auto&& entity : pairs(luaScene)) {
		scene.push_back(parseEntityData(entity.second));
	}
	return scene;
}
