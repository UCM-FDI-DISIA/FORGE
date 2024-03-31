#include "MainForge.h"
#include "Time.h"

#include "RenderManager.h"
#include "SceneManager.h"
#include "Input.h"
/*
#include "PhysicsManager.h"
#include "AudioManager.h"
#include "LoadManager.h"
#include "UIManager.h"
*/
#include <iostream>


std::unique_ptr<MainForge> MainForge::instance = nullptr;

MainForge::MainForge() :
	time(*Time::getInstance()),
	renderManager(*RenderManager::getInstance()), 
	sceneManager(*SceneManager::getInstance()),
	inputManager(*Input::getInstance())/*,
	audioManager(*AudioManager::getInstance()),
	loadManager(*LoadManager::getInstance()),
	physicsManager(*PhysicsManager::getInstance()),
	uiManager(*UIManager::getInstance())*/ {
}

MainForge::~MainForge() {
	sceneManager.cleanUp();
}

void MainForge::manageFixedUpdates() {
	fixedUpdateTimer += Time::deltaTime;
	while (fixedUpdateTimer >= Time::fixedDeltaTime) {
		// physicsManager.update();
		sceneManager.fixedUpdate();
		fixedUpdateTimer -= Time::fixedDeltaTime;
	}
}

void MainForge::update() {
	inputManager.update();
	sceneManager.update();
	//audioManager.update();
}

void MainForge::refresh() {
	sceneManager.refresh();
	inputManager.refresh();
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
		refresh();
		if (!render()) {
			std::cerr << "Could not render." << std::endl;
			break;
		}
	}
}

void MainForge::exit() {
	isRunning = false;
}