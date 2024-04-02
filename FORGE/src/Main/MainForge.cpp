#include "MainForge.h"
#include "TimeForge.h"

#include "RenderManager.h"
#include "SceneManager.h"
#include "Input.h"
#include "AudioManager.h"
#include "LoadManager.h"
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

using namespace forge;

bool MainForge::initialized = false;
std::unique_ptr<MainForge> MainForge::instance = std::unique_ptr<MainForge>(new MainForge());

MainForge::MainForge() :
	isRunning(false),
	fixedUpdateTimer(0.0),
	time(*Time::getInstance()),
	renderManager(*RenderManager::getInstance()),
	sceneManager(*SceneManager::getInstance()),
	inputManager(*Input::getInstance()),
	audioManager(*AudioManager::getInstance()),
	loadManager(*(new LoadManager()))/*,
	physicsManager(*PhysicsManager::getInstance()),
	uiManager(*UIManager::getInstance())*/ {
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

void MainForge::initFactory() {
	Factory& f = *Factory::getInstance();
	f.registerComponent<Transform>();
	f.registerComponent<Mesh>();
	f.registerComponent<Light>();
	f.registerComponent<Camera>();
	f.registerComponent<AudioSource>();
	f.registerComponent<AudioListener>();
}

void MainForge::init(std::string const& luaConfigPath) {
	initialized = true;
	initFactory();
	/* Config:
	nombre ventana
	mapa de audio
	escenas
	¿resources.cfg?
	ui
	*/
	//loadManager.init(luaConfigPath);
	renderManager.setup("mamawebo"/*loadManager.getWindowName()*/);

	//physicsManager.init();???
	//UIManager.init();???
}

void MainForge::shutDown() {
	sceneManager.cleanUp();
	delete& loadManager;
	initialized = false;
}

void MainForge::mainLoop() {
	isRunning = true;
	time.initDT();
	while (isRunning) {
		time.updateDT();
		manageFixedUpdates();
		update();
		if (!render()) {
			std::cerr << "Could not render." << std::endl;
			break;
		}
		inputManager.refresh();
	}
}

void MainForge::Init(std::string const& luaConfigPath) {
	if (!initialized) {
		instance->init(luaConfigPath);
	}
}

void MainForge::MainLoop() {
	if (initialized && !instance->isRunning) {
		instance->mainLoop();
	}
}

void MainForge::ShutDown() {
	if (initialized && !instance->isRunning) {
		instance->shutDown();
	}
}

void MainForge::Exit() {
	if (initialized) {
		instance->isRunning = false;
	}
}