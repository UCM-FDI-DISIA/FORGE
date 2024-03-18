// Este archivo es para que se suba la carpeta src/Render a Github
#define _CRTDBG_MAP_ALLOC
#define SDL_MAIN_HANDLED
#include <stdlib.h>
#include <crtdbg.h>
#include "RenderManager.h"

#include "SceneManager.h"
#include "Scene.h"
#include "LuaForge.h"
#include "EcsLoad.h"
#include "Input.h"
#include "Factory.h"
#include "Transform.h"
#include "Mesh.h"
#include "Light.h"
#include "Camera.h"
#include "TestMovement.h"
#include "test.h"
#include "PhysicsManager.h"
#include "RigidBody.h"

#define FIXED_UPDATE_RATE 0.02

void factory() {
	Factory& f = *Factory::getInstance();
	f.registerComponent<Transform>();
	f.registerComponent<Mesh>();
	f.registerComponent<Light>();
	f.registerComponent<Camera>();
	f.registerComponent<TestMovement>();
	f.registerComponent<RigidBody>();
}


int main(int argc, char* argv[]) {
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	factory();
	RenderManager& render = *RenderManager::getInstance();
    render.setup("Test FORGE");
	LuaForge* lf = new LuaForge();
	EcsLoad ecs("scenetest.lua", *lf);
    SceneManager& sceneManager = *SceneManager::getInstance();
	PhysicsManager& phyisicsManager = *PhysicsManager::getInstance();
	phyisicsManager.initPhysics();


    Input& input = *Input::getInstance();
    sceneManager.changeScene("Test");
	testFisico* myTest = new testFisico();

	double deltaTime = 0;
	double fixedUpdateTimer = 0;

    while (!input.keyUp(K_ESC)) {
		double start = SDL_GetTicks();
        input.refresh();
        input.update();
        sceneManager.update();
		sceneManager.refresh();
        if(!render.render())
			break;

		double end = SDL_GetTicks();
		deltaTime = end - start;

		fixedUpdateTimer += deltaTime;

		while (fixedUpdateTimer >= FIXED_UPDATE_RATE) {
			sceneManager.fixedUpdate();
			phyisicsManager.updatePhysics();
			fixedUpdateTimer -= FIXED_UPDATE_RATE;
		}
    }
	delete lf;
	sceneManager.cleanUp();

    return 0;
}

