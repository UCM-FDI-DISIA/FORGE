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
#include "ForgeError.h"
#include "Factory.h"
#include "Transform.h"
#include "Mesh.h"
#include "Light.h"
#include "Camera.h"
#include "AudioSource.h"
#include "AudioListener.h"

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

bool LoadManager::loadScenes(LuaRef const& config) {
	LuaRef scenes = config["scenesFile"];
	if (!scenes.isString()) {
		throwError(false, "No se proporciono un archivo de escenas o no es un string.");
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
		throwError(false, "No se encontro un bloque de audios a cargar.");
	}
	AudioManager& am = *AudioManager::getInstance();
	for (auto&& audio : pairs(audioRef)) {
		if (!audio.first.isString()) {
			throwError(false, "Nombre de audio no valido.");
		}
		if (!audio.second.isString()) {
			throwError(false, "Ruta al audio no existe o no es un string");
		}
		am.addSound(audio.first.cast<std::string>(), audio.second.cast<std::string>());
	}
	return true;
}

bool LoadManager::loadGame(LuaRef const& config, std::string& gameName) {
#ifdef _DEBUG
	std::string reading = "debugGame";
#else 
	std::string reading = "game";
#endif
	LuaRef game = config[reading];
	if (!game.isString()) {
		throwError(false, "\"" << reading << "\" no se proporciono o no es un string.");
	}
	gameName = game.cast<std::string>();
	if (!gameLoader->init(gameName)) {
		throwError(false, "No se pudo cargar el juego.");
	}
	return true;
}

bool LoadManager::loadComponents() {
	factory.registerComponent<Transform>();
	factory.registerComponent<Mesh>();
	factory.registerComponent<Light>();
	factory.registerComponent<Camera>();
	factory.registerComponent<AudioSource>();
	factory.registerComponent<AudioListener>();
	return gameLoader->registerComponents(factory);
}

bool LoadManager::loadAssets(LuaRef const& config) {
	LuaRef assets = config["assetsFile"];
	if (!assets.isString()) {
		throwError(true, "No se proporciono un archivo con assets a cargar o el valor introducido no es un string.");
	}
	if (!luaForge->doFile(assets.cast<std::string>())) {
		throwError(false, "No hay escenas que cargar.");
	}
	if (!loadAudio()) {
		throwError(false, "No se pudo cargar el audio correctamente");
	}
	
	return true;
}

bool LoadManager::loadInitialScene(LuaRef const& config) {
	LuaRef initScene = config["initialScene"];
	if (!initScene.isString()) {
		throwError(false, "No se proporciono una escena inicial o no es un string.");
	}
	sceneManager.changeScene(initScene.cast<std::string>());
	return true;
}

LoadManager::LoadManager() :
	gameLoader(new GameLoader()),
	luaForge(new LuaForge()),
	sceneManager(*SceneManager::getInstance()),
	renderManager(*RenderManager::getInstance()),
	factory(*Factory::getInstance()) {
}

bool LoadManager::init(std::string const& configFile) {
	if (!luaForge->doFile(configFile)) {
		throwError(false, "No se proporciono un archivo de configuracion, no se ha encontrado o no tiene formato correcto.");
	}

	LuaRef config = getGlobal(luaForge->getState(), "Config");
	if (!config.isTable()) {
		throwError(false, "No se pudo encontrar la configuracion en el archivo proporcionado.");
	}
	std::string gameName;
	if (!loadGame(config, gameName)) {
		throwError(false, "No se pudo cargar el juego.");
	}
	if (!loadComponents()) {
		throwError(false, "No se pudieron cargar los componentes.");
	}
	if (!loadAssets(config)) {
		throwError(false, "No se pudieron cargar los assets.");
	}
	if (!loadScenes(config)) {
		throwError(false, "No se pudieron cargar las escenas.");
	}
	renderManager.setup(gameName);
	if (!loadInitialScene(config)) {
		throwError(false, "No se pudo cargar la escena inicial.");
	}
	return true;
}

bool LoadManager::cleanUp() {
	factory.cleanUp();
	return gameLoader->free();
}

LoadManager::~LoadManager() {
	delete luaForge;
	delete gameLoader;
}