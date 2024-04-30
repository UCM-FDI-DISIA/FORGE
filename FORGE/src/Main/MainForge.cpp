#include "MainForge.h"
#include "TimeForge.h"

#include "RenderManager.h"
#include "SceneManager.h"
#include "Input.h"
#include "AudioManager.h"
#include "LoadManager.h"
#include "GameLoader.h"
#include "PhysicsManager.h"
#include "GUIManager.h"
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
	physicsManager(*PhysicsManager::GetInstance()),
	guiManager(*GUIManager::GetInstance())
	{
}

bool MainForge::init(std::string const& configPath) {
	initialized = true;
	finished = false;
	if (!loadManager.init(configPath)) {
		finished = true;
		return false;
	}

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
	return renderManager.render();
}

bool MainForge::shutDown() {
	bool result = true;
	sceneManager.cleanUp();
	guiManager.cleanUp();
	result = loadManager.cleanUp();
	delete& loadManager;
	initialized = false;
	return result;
}

bool MainForge::mainLoop() {
	bool result = true;
	isRunning = true;
	time.init();
	while (isRunning) {
		time.update();
		manageFixedUpdates();
		update();
		if (!render()) {
			reportError("No se pudo renderizar el juego.");
			result = false;
			Exit();
		}
		
		if (inputManager.isWindowClosed()) {
			Exit();
		}
		else if (inputManager.isWindowResized()) {
			renderManager.resizeWindow();
			guiManager.resizeWindow();
		}

		inputManager.refresh();
	}
	finished = true;
	return result;
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
		GUIManager::Init();
		if (instance == nullptr) instance = std::unique_ptr<MainForge>(new MainForge());
		return instance->init(configPath);
	}
	throwError(false, "No se puede inicializar FORGE cuando ya esta inicializado.");
}

bool MainForge::MainLoop() {
	if (initialized && !instance->isRunning) {
		return instance->mainLoop();
	}
	throwError(false, "No se puede activar el bucle principal si no se ha inicializado FORGE o si ya esta corriendo.");
}

bool MainForge::ShutDown() {
	if (initialized && instance->finished) {
		if (!instance->shutDown()) {
			throwError(false, "No se pudo apagar FORGE correctamente.");
		}
		return true;
	}
	throwError(false, "No se no se puede apagar FORGE si no se ha inicializado o no ha finalizado sus operaciones.");
}

void MainForge::Exit() {
	if (initialized && instance->isRunning) {
		instance->isRunning = false;
	}
#ifdef _DEBUG
	else {
		reportError("No se puede salir de la aplicacion si no esta inicializada o no esta corriendo.");
	}
#endif
}