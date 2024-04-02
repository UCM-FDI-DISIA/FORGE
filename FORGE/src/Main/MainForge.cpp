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
#include <iostream>

using namespace forge;

std::unique_ptr<MainForge> MainForge::instance = nullptr;

MainForge::MainForge() :
	time(*Time::getInstance()),
	renderManager(*RenderManager::getInstance()), 
	sceneManager(*SceneManager::getInstance()),
	inputManager(*Input::getInstance()),
	audioManager(*AudioManager::getInstance()),
	loadManager(*(new LoadManager()))/*,
	physicsManager(*PhysicsManager::getInstance()),
	uiManager(*UIManager::getInstance())*/ {
}

MainForge::~MainForge() {
	sceneManager.cleanUp();
	delete &loadManager;
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

MainForge* MainForge::getInstance() {
	if (instance != nullptr) return instance.get();
	return (instance = std::unique_ptr<MainForge>(new MainForge())).get();
}

void MainForge::init(std::string luaConfigPath) {
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

void MainForge::mainLoop() {
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

void MainForge::exit() {
	isRunning = false;
}