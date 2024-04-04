#include "MainForge.h"
#include "TimeForge.h"

#include "RenderManager.h"
#include "SceneManager.h"
#include "Input.h"
#include "AudioManager.h"
#include "LoadManager.h"
#include "GameLoad.h"
/*
#include "PhysicsManager.h"
#include "UIManager.h"
*/

#include "Factory.h"
#include "Transform.h"
#include "Mesh.h"
#include "Light.h"
#include "Camera.h"
#include "AudioManager.h"
#include "AudioListener.h"
#include "AudioSource.h"

#include <iostream>
#include <windows.h>

using namespace forge;


bool MainForge::initialized = false;
std::unique_ptr<MainForge> MainForge::instance = nullptr;

MainForge::MainForge() :
	isRunning(false),
	finished(false),
	fixedUpdateTimer(0.0),
	time(*Time::getInstance()),
	factory(*Factory::getInstance()),
	renderManager(*RenderManager::getInstance()),
	sceneManager(*SceneManager::getInstance()),
	inputManager(*Input::getInstance()),
	audioManager(*AudioManager::getInstance()),
	loadManager(*(new LoadManager()))/*,
	physicsManager(*PhysicsManager::getInstance()),
	uiManager(*UIManager::getInstance())*/ {
}

void MainForge::initFactory() {
	factory.registerComponent<Transform>();
	factory.registerComponent<Mesh>();
	factory.registerComponent<Light>();
	factory.registerComponent<Camera>();
	factory.registerComponent<AudioSource>();
	factory.registerComponent<AudioListener>();
	loadManager.getGame().registerComponents(factory);
}

void MainForge::init(std::string const& luaConfigPath) {
	initialized = true;
	finished = false;
	if (!loadManager.init("Assets/assets.forge.lua", "scenetest.lua")) return;
	initFactory();
	/* Config:
	nombre ventana
	mapa de audio
	escenas
	escena inicial
	¿resources.cfg?
	ui
	*/
	//loadManager.init(luaConfigPath);
	renderManager.setup("mamawebo"/*loadManager.getWindowName()*/);
	sceneManager.changeScene("Test");

	//physicsManager.init();???
	//UIManager.init();???
}

void MainForge::manageFixedUpdates() {
	fixedUpdateTimer += Time::deltaTime;
	while (fixedUpdateTimer >= Time::fixedDeltaTime) {
		// physicsManager.updatePhysics();
		sceneManager.fixedUpdate();
		fixedUpdateTimer -= Time::fixedDeltaTime;
	}
}

void MainForge::update() {
	inputManager.update();
	sceneManager.update();
	audioManager.update();
}

bool MainForge::render() {
	return renderManager.render() /*&& uiManager.render()*/;
}

void MainForge::shutDown() {
	sceneManager.cleanUp();
	factory.cleanUp();
	loadManager.cleanUp();
	delete& loadManager;
	initialized = false;
}

void MainForge::mainLoop() {
	isRunning = true;
	time.init();
	while (isRunning) {
		time.update();
		manageFixedUpdates();
		update();
		if (!render()) {
			std::cerr << "Could not render." << std::endl;
			break;
		}
		
		if (inputManager.isWindowClosed()) {
			Exit();
		}

		inputManager.refresh();
	}
	finished = true;
}

void MainForge::Init(std::string const& luaConfigPath) {
	if (!initialized) {
		if (instance == nullptr) instance = std::unique_ptr<MainForge>(new MainForge());
		instance->init(luaConfigPath);
	}
}

void MainForge::MainLoop() {
	if (initialized && !instance->isRunning) {
		instance->mainLoop();
	}
}

void MainForge::ShutDown() {
	if (initialized && instance->finished) {
		instance->shutDown();
	}
}

void MainForge::Exit() {
	if (initialized && instance->isRunning) {
		instance->isRunning = false;
	}
}