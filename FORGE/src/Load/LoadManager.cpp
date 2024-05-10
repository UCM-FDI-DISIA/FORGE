#include "LoadManager.h"
#include <set>
#include <exception>
#include <lua.hpp>
#pragma warning(push)
#pragma warning(disable : 4244)
#pragma warning(disable : 4267)
#pragma warning(disable : 26439)
#pragma warning(disable : 26495)
#include <LuaBridge/LuaBridge.h>
#pragma warning(pop)
#include "LuaForge.h"
#include "EntityData.h"
#include "GameLoader.h"
#include "AudioManager.h"
#include "SceneManager.h"
#include "RenderManager.h"
#include "PhysicsManager.h"
#include "ComponentData.h"
#include "GUIManager.h"
#include "ForgeError.h"
#include "Factory.h"
#include "Transform.h"
#include "RectTransform.h"
#include "Mesh.h"
#include "Light.h"
#include "Camera.h"
#include "Animator.h"
#include "Billboard.h"
#include "BillboardSet.h"
#include "ParticleSystem.h"
#include "AudioSource.h"
#include "AudioListener.h"
#include "Collider.h"
#include "RigidBody.h"
#include "Text.h"
#include "Image.h"
#include "Button.h"
#include "ProgressBar.h"


using namespace luabridge;

bool LoadManager::extractEntityValues(EntityData& entityData, LuaRef& handler, LuaRef& group, LuaRef& components) {
	if (handler.isString()) {
		entityData.handler = handler.tostring();
	}
	if (group.isString()) {
		entityData.group = group.tostring();
		sceneManager.addGroup(entityData.group);
	}
	if (components.isTable()) {
		for (auto&& component : pairs(components)) {
			if (!component.first.isString()) {
				throwError(false, "Nombre de componente no valido");
			}
			std::string id = component.first.tostring();
			if (!component.second.isTable() && !(component.second.isNumber() && component.second.cast<int>() == 0)) {
				throwError(false, "Datos de componente \"" << id << "\" no validos");
			}
			// Crear copias de los LuaRef para no perder las referencias de los datos en la pila
			LuaRef* data = new LuaRef(component.second);
			ComponentData*& comp = entityData.components[Factory::GetInstance()->getComponentOrder(id)];
			if (comp != nullptr) {
				delete comp;
			}
			comp = new ComponentData(id, data);
		}
	}
	return true;
}

bool LoadManager::extractChildren(EntityData& entityData, LuaRef& children) {
	if (!children.isTable()) {
		return true;
	}
	if (!entityData.isBlueprint) {
		for (auto&& child : pairs(children)) {
			EntityData* ed = parseEntityData(child.second);
			if (ed == nullptr) {
				throwError(false, "No se pudo crear correctamente el hijo de la entidad");
			}
			entityData.children.push_back(ed);
		}
		return true;
	}
	for (auto&& child : pairs(children)) {
		LuaRef index = child.second["index"];
		// Si index no es una tabla con dos elementos, un numero y un string,
		bool aux = index.isTable() && index.length() == 2 && index[0].isNumber() && index[1].isString();
		int i = -1;
		if (aux) {
			i = index[0].cast<int>();
			// si el index es un entero no valido
			aux = aux && (i >= 0 && i < static_cast<int>(entityData.children.size()));
		}
		// Si se cumplen las condiciones anteriores se agrega el hijo como nuevo elemento
		if (!aux) {
			EntityData* ed = parseEntityData(child.second);
			if (ed == nullptr) {
				throwError(false, "No se pudo crear correctamente el hijo de la entidad basada en blueprint");
			}
			entityData.children.push_back(ed);
		}
		else {
			std::string mode = index[1].tostring();
			EntityData*& childData = entityData.children[i];
			if (mode == "modify") {
				// si estas modificando un blueprint lo copias
				if (childData->isBlueprint) {
					childData = new EntityData(*childData);
				}
				if (!modifyChildrenData(*childData, child.second)) {
					throwError(false, "No se pudo modificar correctamente el hijo de la entidad basada en blueprint");
				}
			}
			else /*if (delete || replace)*/ {
				if (childData != nullptr && !childData->isBlueprint) {
					delete childData;
				}
				childData = nullptr;
				//Modo por defecto "replace", si no se ha especificado modo o el modo es incorrecto
				if (mode != "delete") {
					childData = parseEntityData(child.second);
					if (childData == nullptr) {
						throwError(false, "No se pudo reemplazar correctamente el hijo de la entidad basada en blueprint");
					}
					entityData.children.push_back(childData);
				}
			}
		}
	}
	return true;
}

bool LoadManager::modifyChildrenData(EntityData& childData, LuaRef& data) {
	LuaRef
		group = data["group"],
		handler = data["handler"],
		components = data["components"],
		children = data["children"];
	if (!extractEntityValues(childData, handler, group, components)) {
		throwError(false, "No se pudo leer correctamente la modificacion del hijo de la entidad basada en blueprint");
	}
	bool wasBlueprint = childData.isBlueprint;
	childData.isBlueprint = true;
	if (!extractChildren(childData, children)) {
		throwError(false, "No se pudo leer correctamente la modificacion de los hijos del hijo de la entidad basada en blueprint");
	}
	childData.isBlueprint = wasBlueprint;
	return true;
}


EntityData* LoadManager::parseEntityData(LuaRef& luaEntity) {
	LuaRef
		group = luaEntity["group"],
		handler = luaEntity["handler"],
		blueprint = luaEntity["blueprint"],
		components = luaEntity["components"],
		children = luaEntity["children"];

	EntityData* entityData;
	if (!blueprint.isString()) {
		entityData = new EntityData();
		if (!extractEntityValues(*entityData, handler, group, components) || 
			!extractChildren(*entityData, children)) {
			delete entityData;
			throwError(nullptr, "No se pudo crear correctamente la entidad");
		}
	}
	else {
		entityData = sceneManager.getEntityBlueprint(blueprint.tostring());
		if (handler.isString() || group.isString() || components.isTable() || children.isTable()) {
			entityData = new EntityData(*entityData);
			entityData->isBlueprint = true;
			if (!extractEntityValues(*entityData, handler, group, components) ||
				!extractChildren(*entityData, children)) {
				delete entityData;
				throwError(nullptr, "No se pudo crear correctamente la entidad basada en blueprint");
			}
			entityData->isBlueprint = false;
		}
	}

	return entityData;
}

std::vector<EntityData*> LoadManager::parseScene(LuaRef& luaScene) {
	if (!luaScene.isTable()) {
		throwError(std::vector<EntityData*>(), "No se pudo parsear la escena correctamente");
	}
	std::vector<EntityData*> scene;
	for (auto&& entity : pairs(luaScene)) {
		EntityData* entityData = parseEntityData(entity.second);
		if (entityData == nullptr) {
			throwError(std::vector<EntityData*>(), "No se pudo parsear la escena correctamente");
		}
		scene.push_back(entityData);
	}
	return scene;
}

bool LoadManager::loadScenes(LuaRef const& config) {
	LuaRef scenes = config["scenesFile"];
	if (!scenes.isString()) {
		throwError(false, "No se proporciono un archivo de escenas o no es un string.");
	}

	std::string path = scenes.tostring();
	if (!luaForge->doFile(path)) {
		throwError(false, "No se pudo abrir el archivo de escenas.");
	}
	lua_State* lua = luaForge->getState();
	sceneManager.setLuaState(lua);
	LuaRef entityBlueprints = LuaRef(lua);
	LuaRef keepBetweenScenes = LuaRef(lua);
	LuaRef sceneBlueprints = LuaRef(lua);
	try {
		entityBlueprints = LuaRef::fromStack(lua, -3);
		keepBetweenScenes = LuaRef::fromStack(lua, -2);
		sceneBlueprints = LuaRef::fromStack(lua, -1);
	}
	catch (std::exception e) {
		throwError(false, "Faltaron valores en el archivo de escena.");
	}
	if (entityBlueprints.isTable()) {
		for (auto&& entity : pairs(entityBlueprints)) {
			if (entity.second.isString()) {
				throwError(false, "Nombre de blueprint no valido");
			}
			EntityData* blueprint = parseEntityData(entity.second);
			if (blueprint == nullptr) {
				throwError(false, "No se pudo crear correctamente el blueprint");
			}
			blueprint->isBlueprint = true;
			sceneManager.addEntityBlueprint(entity.first.tostring(), blueprint);
		}
	}
	if (keepBetweenScenes.isTable()) {
		for (auto&& entity : pairs(keepBetweenScenes)) {
			EntityData* entityData = parseEntityData(entity.second);
			if (entityData == nullptr) {
				throwError(false, "No se pudo crear correctamente la entidad en KeepBetweenScenes");
			}
			sceneManager.addKeptBetweenScenes(entityData);
		}
	}
	if (sceneBlueprints.isTable()) {
		for (auto&& scene : pairs(sceneBlueprints)) {
			if (scene.second.isString()) {
				throwError(false, "Nombre de escena no valido");
			}
			std::vector<EntityData*> parsedScene = parseScene(scene.second);
			if (static_cast<int>(parsedScene.size()) <= 0) {
				throwError(false, "Escena no valida");
			}
			sceneManager.addSceneBlueprint(scene.first.tostring(), parsedScene);
		}
	}
	return true;
}

bool LoadManager::loadAudio() {
	LuaRef audioRef = getGlobal(luaForge->getState(), "Audio");
	if (audioRef.isNil() || !audioRef.isTable()) {
		throwError(false, "No se encontro un bloque de audios a cargar.");
	}
	AudioManager& am = *AudioManager::GetInstance();
	for (auto&& audio : pairs(audioRef)) {
		if (!audio.first.isString()) {
			throwError(false, "Nombre de audio no valido.");
		}
		if (!audio.second.isString()) {
			throwError(false, "Ruta al audio no existe o no es un string");
		}
		am.addSound(audio.first.tostring(), audio.second.tostring());
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
	gameName = game.tostring();
	if (!gameLoader->init(gameName)) {
		throwError(false, "No se pudo cargar el juego.");
	}
	return true;
}

bool LoadManager::loadWindow(uint32_t& width, uint32_t& height) {
	LuaRef window = getGlobal(luaForge->getState(), "Window");
	if (!window.isTable()) {
		throwError(false, "No se pudo encontrar la configuracion de ventana en el archivo proporcionado.");
	}
	LuaRef w = window["width"];
	LuaRef h = window["height"];
	if (!w.isInstance<uint32_t>()) {
		throwError(false, "Formato de anchura incorrecto.");
	}
	width = w.cast<uint32_t>();
	if (!h.isInstance<uint32_t>()) {
		throwError(false, "Formato de altura incorrecto.");
	}
	height = h.cast<uint32_t>();
	return true;
}

bool LoadManager::loadComponents() {
	factory.registerComponent<Transform>();
	factory.registerComponent<RectTransform>();
	factory.registerComponent<Mesh>();
	factory.registerComponent<Light>();
	factory.registerComponent<Camera>();
	factory.registerComponent<Animator>();
	factory.registerComponent<Billboard>();
	factory.registerComponent<BillboardSet>();
	factory.registerComponent<ParticleSystem>();
	factory.registerComponent<AudioSource>();
	factory.registerComponent<AudioListener>();
	factory.registerComponent<Collider>();
	factory.registerComponent<RigidBody>();
	factory.registerComponent<Text>();
	factory.registerComponent<Image>();
	factory.registerComponent<Button>();
	factory.registerComponent<ProgressBar>();
	return gameLoader->registerComponents(factory);
}

bool LoadManager::loadPhysics() {
	LuaRef config = getGlobal(luaForge->getState(), "Physics");
	if (!config.isTable()) {
		throwError(false, "No se ha proporcionado una configuracion de fisicas");
	}
	LuaRef layers = config["layers"];
	if (!layers.isTable()) {
		throwError(false, "No se ha proporcionado una matriz de capas de colision");
	}
	struct orderLayers {
		bool operator()(std::pair<std::string, std::vector<bool>> const& a, std::pair<std::string, std::vector<bool>> const& b) const {
			return a.second.size() < b.second.size();
		}
	};

	std::set<std::pair<std::string, std::vector<bool>>, orderLayers> layersVector;
	for (auto&& layer : pairs(layers)) {
		if (!layer.first.isString()) {
			throwError(false, "Nombre de capa de colision no valido.");
		}
		if (!layer.second.isTable()) {
			throwError(false, "No se pudieron leer las interacciones con capas de \"" << layer.first.tostring() << "\".");
		}
		std::vector<bool> layerVector;
		for (auto&& interaction : pairs(layer.second)) {
			if (!interaction.second.isBool()) {
				throwError(false, "Valor de interaccion con la capa \"" << layer.first.tostring() << "\" no valido.");
			}
			layerVector.push_back(interaction.second.cast<bool>());
		}
		layersVector.insert({ layer.first, layerVector });
	}

	for (auto const& layer : layersVector) {
		int i = 0;
		auto layerI = layersVector.begin();
		physicsManager.addLayer(layer.first);
		std::vector<std::string> interactions;
		for (auto const& interacts : layer.second) {
			if (interacts) {
				interactions.push_back(layerI->first);
			}
			++layerI;
		}
		if (!physicsManager.setCollideWith(layer.first, interactions)) {
			throwError(false, "No se pudieron inicializar las capas de colision");
		}
	}
#ifdef _DEBUG
	LuaRef debugBool = config["debug"];
	if (!debugBool.isBool()) {
		throwError(false, "PHYSICS DEBUG: El valor introducido no es un booleano valido");
	}
	physicsManager.setDebug(debugBool);
#endif // _DEBUG
	
	return true;
}

bool LoadManager::loadAssets(LuaRef const& config) {
	LuaRef assets = config["assetsFile"];
	if (!assets.isString()) {
		throwError(true, "No se proporciono un archivo con assets a cargar o el valor introducido no es un string.");
	}
	if (!luaForge->doFile(assets.tostring())) {
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
	return sceneManager.createFirstScene(initScene.tostring());

}

LoadManager::LoadManager() :
	gameLoader(new GameLoader()),
	luaForge(new LuaForge()),
	sceneManager(*SceneManager::GetInstance()),
	renderManager(*RenderManager::GetInstance()),
	physicsManager(*PhysicsManager::GetInstance()),
	guiManager(*GUIManager::GetInstance()),
	factory(*Factory::GetInstance()) {
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
	uint32_t width, height;
	if (!loadWindow(width, height)) {
		throwError(false, "No se pudo cargar la ventana.");
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
	if (!renderManager.setup(gameName, width, height)) {
		throwError(false, "No se pudo iniciar el sistema de renderizado.");
	}
	if (!guiManager.setup()) {
		throwError(false, "No se pudo iniciar la interfaz.");
	}
	if (!loadPhysics()) {
		throwError(false, "No se pudo cargar la configuracion de fisicas.");
	}
	physicsManager.setup();
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