#include "MainForge.h"
#include "TimeForge.h"

#include "RenderManager.h"
#include "SceneManager.h"
#include "Input.h"
#include "AudioManager.h"
#include "LoadManager.h"
#include "GameLoader.h"
#include "PhysicsManager.h"
//#include "UIManager.h"
#include "ForgeError.h"

using namespace forge;


bool MainForge::initialized = false;
std::unique_ptr<MainForge> MainForge::instance = nullptr;

MainForge::MainForge() :
	isRunning(false),
	finished(false),
	fixedUpdateTimer(0.0),
	time(*Time::GetInstance()),
	renderManager(*RenderManager::GetInstance()),
	sceneManager(*SceneManager::GetInstance()),
	inputManager(*Input::GetInstance()),
	audioManager(*AudioManager::GetInstance()),
	loadManager(*(new LoadManager())),
	physicsManager(*PhysicsManager::GetInstance())
	//uiManager(*UIManager::getInstance()) 
	{
}

bool MainForge::init(std::string const& configPath) {
	initialized = true;
	finished = false;
	if (!loadManager.init(configPath)) {
		finished = true;
		return false;
	}

	//physicsManager.Init();
	//UIManager.init();???
	return true;
}

void MainForge::manageFixedUpdates() {
	fixedUpdateTimer += Time::deltaTime;
	while (fixedUpdateTimer >= Time::fixedDeltaTime) {
		physicsManager.updatePhysics();
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
#ifdef _DEBUG
	physicsManager.drawDebug();
#endif // _DEBUG
	return renderManager.render() /*&& uiManager.render()*/;
}

void MainForge::shutDown() {
	sceneManager.cleanUp();
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
			reportError("No se pudo renderizar el juego.");
			Exit();
		}
		
		if (inputManager.isWindowClosed()) {
			Exit();
		}

		inputManager.refresh();
	}
	finished = true;
}

bool MainForge::Init(std::string const& configPath) {
	if (!initialized) {
		if (!AudioManager::Init()) {
			throwError(false, "No se pudo iniciar el sistema de audio.");
		}
		RenderManager::Init();
		SceneManager::Init();
		PhysicsManager::Init();
		if (!Input::Init()) {
			throwError(false, "No se pudo iniciar el sistema de entrada.");
		}
		if (instance == nullptr) instance = std::unique_ptr<MainForge>(new MainForge());
		return instance->init(configPath);
	}
	return false;
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