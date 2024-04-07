#include "LoadManager.h"
#include <lua.hpp>
#pragma warning(push)
#pragma warning(disable : 26439)
#include <LuaBridge/LuaBridge.h>
#pragma warning(pop)
#include "LuaForge.h"
#include "GameLoader.h"
#include "AudioManager.h"
#include "SceneManager.h"
#include "EntityData.h"
#include "ComponentData.h"
#include "RenderManager.h"

using namespace luabridge;
bool isString(LuaRef const& ref) {
	return !ref.isNil() && ref.isInstance<std::string>();
}
void reportError(std::string const& error) {
#ifdef _DEBUG
	std::cerr << error;
#endif
}
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

bool LoadManager::loadScenes(LuaRef const& config) {
	LuaRef scenes = config["scenesFile"];
	if (!isString(scenes)) {
		reportError("No se proporciono un archivo de escenas o no es un string.\n");
		return false;
	}

	std::string realPath = scenes.cast<std::string>();
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
	return true;
}

bool LoadManager::loadAudio() {
	LuaRef audioRef = getGlobal(luaForge->getState(), "Audio");
	if (audioRef.isNil() || !audioRef.isTable()) {
		reportError("No se encontro un bloque de audios a cargar.\n");
		return true;
	}
	AudioManager& am = *AudioManager::getInstance();
	for (auto&& audio : pairs(audioRef)) {
		if (!isString(audio.first)) {
			reportError("Nombre de audio no valido.\n");
			return false;
		}
		if (!isString(audio.second)) {
			reportError("Ruta al audio no existe o no es un string\n");
			return false;
		}
		am.addSound(audio.first.cast<std::string>(), audio.second.cast<std::string>());
	}
	return true;
}

bool LoadManager::loadGame(LuaRef const& config) {
#ifdef _DEBUG
	std::string reading = "debugGame";
#else 
	std::string reading = "game";
#endif
	LuaRef game = config[reading];
	if (!isString(game)) {
		reportError("\"" + reading + "\" no se proporciono o no es un string.\n");
		return false;
	}
	gameName = game.cast<std::string>();
	if (!gameLoader->init(gameName)) {
		reportError("No se pudo cargar el juego.\n");
		return false;
	}
	return true;
}

bool LoadManager::loadAssets(LuaRef const& config) {
	LuaRef assets = config["assetsFile"];
	if (!isString(assets)) {
		reportError("No se proporciono un archivo con assets a cargar o el valor introducido no es un string.\n");
	}
	else {
		if (!luaForge->doFile(assets.cast<std::string>())) {
			reportError("No hay escenas que cargar.\n");
			return false;
		}
		if (!loadAudio()) {
			reportError("No se pudo cargar el audio correctamente");
			return false;
		}
	}
	return true;
}

bool LoadManager::loadInitialScene(LuaRef const& config) {
	LuaRef initScene = config["initialScene"];
	if (!isString(initScene)) {
		reportError("No se proporciono una escena inicial o no es un string.\n");
		return false;
	}
	initialScene = initScene.cast<std::string>();
}

LoadManager::LoadManager() :
	gameLoader(new GameLoader()),
	luaForge(new LuaForge()),
	sceneManager(*SceneManager::getInstance()),
	renderManager(*RenderManager::getInstance()){
}

bool LoadManager::init(std::string const& configFile) {
	if (!luaForge->doFile(configFile)) {
		reportError("No se proporciono un archivo de configuracion, no se ha encontrado o no tiene formato correcto.\n");
		return false;
	}

	LuaRef config = getGlobal(luaForge->getState(), "Config");
	if (config.isNil() || !config.isTable()) {
		reportError("No se pudo encontrar la configuracion en el archivo proporcionado.\n");
		return false;
	}

	if (!loadGame(config)) {
		reportError("No se pudo cargar el juego.\n");
		return false;
	}
	if (!loadAssets(config)) {
		reportError("No se pudieron cargar los assets.\n");
		return false;
	}
	if (!loadScenes(config)) {
		reportError("No se pudieron cargar las escenas.\n");
		return false;
	}
	//renderManager.setup(gameName);
	if (!loadInitialScene(config)) {
		reportError("No se pudo guardar la escena inicial.\n");
		return false;
	}
	return true;
}

bool LoadManager::init(std::string const& assetsFile, std::string const& scenesFile) {
#ifdef _DEBUG
	gameLoader->init("Demo_d");
#else
	gameLoad->init("Demo");
#endif
	if (!luaForge->doFile(assetsFile)) {
		return false;
	}

	if (!loadAudio()) {

	}

	//loadScenes(scenesFile);
	return true;
}

bool LoadManager::cleanUp() {
	return gameLoader->free();
}

GameLoader& LoadManager::getGame() {
	return *gameLoader;
}

std::string const& LoadManager::getGameName() const {
	return gameName;
}

std::string const& LoadManager::getInitialScene() const {
	return initialScene;
}

LoadManager::~LoadManager() {
	delete luaForge;
	delete gameLoader;
}
