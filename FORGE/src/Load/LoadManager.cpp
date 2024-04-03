#include "LoadManager.h"
#include <lua.hpp>
#pragma warning(push)
#pragma warning(disable : 26439)
#include <LuaBridge/LuaBridge.h>
#pragma warning(pop)
#include "LuaForge.h"
#include "GameLoad.h"
#include "AudioManager.h"
#include "SceneManager.h"
#include "EntityData.h"
#include "ComponentData.h"

using namespace luabridge;

void LoadManager::extractEntityValues(EntityData& entityData, LuaRef& handler, LuaRef& group, LuaRef& components) {
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

void LoadManager::extractChildren(EntityData& entityData, LuaRef& children) {
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

void LoadManager::modifyChildrenData(EntityData& childData, LuaRef& data) {
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


EntityData* LoadManager::parseEntityData(LuaRef& luaEntity) {
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

std::vector<EntityData*> LoadManager::parseScene(LuaRef& luaScene) {
	std::vector<EntityData*> scene;
	for (auto&& entity : pairs(luaScene)) {
		scene.push_back(parseEntityData(entity.second));
	}
	return scene;
}

void LoadManager::loadScenes(std::string const& path) {

	std::string realPath = "Assets/scenes/" + path;
	luaForge->doFile(realPath);
	lua_State* lua = luaForge->getState();
	sceneManager.setLuaState(lua);

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

bool LoadManager::loadAudio() {
	LuaRef audioRef = getGlobal(luaForge->getState(), "Audio");
	if (audioRef.isNil() || !audioRef.isTable()) {
		return false;
	}
	AudioManager& am = *AudioManager::getInstance();
	for (auto&& audio : pairs(audioRef)) {
		if (audio.first.isNil() || !audio.first.isInstance<std::string>()) {
			return false;
		}
		if (audio.second.isNil() || !audio.second.isInstance<std::string>()) {
			return false;
		}
		am.addSound(audio.first.cast<std::string>(), audio.second.cast<std::string>());
	}
	return true;
}

LoadManager::LoadManager() :
	gameLoad(new GameLoad()),
	luaForge(new LuaForge()),
	sceneManager(*SceneManager::getInstance()) {
}

bool LoadManager::init(std::string const& assetsFile, std::string const& scenesFile) {
	gameLoad->init("Demo_d");
	if (luaForge->doFile(assetsFile)) {
		return false;
	}

	if (!loadAudio()) {

	}

	loadScenes(scenesFile);
	return true;
}

bool LoadManager::cleanUp() {
	return gameLoad->free();
}

GameLoad& LoadManager::getGame() {
	return *gameLoad;
}

LoadManager::~LoadManager() {
	delete luaForge;
	delete gameLoad;
}
