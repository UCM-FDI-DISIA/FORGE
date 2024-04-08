#define _CRTDBG_MAP_ALLOC
#define SDL_MAIN_HANDLED
#include <stdlib.h>
#include <crtdbg.h>
#include "RenderManager.h"

#include "SceneManager.h"
#include "Scene.h"
#include "LoadManager.h"
#include "EcsLoad.h"
#include "Input.h"
#include "Factory.h"
#include "Transform.h"
#include "Mesh.h"
#include "Light.h"
#include "Camera.h"
#include "PhysicsManager.h"
#include "RigidBody.h"
#include "Animator.h"
#include "ParticleSystem.h"
#include "Billboard.h"
#include "TestComponent.h"

#define FIXED_UPDATE_RATE 20

#include "AudioManager.h"
#include "AudioListener.h"
#include "AudioSource.h"
#include "Sound.h"
#include <SDL_timer.h>

void factory() {
	Factory& f = *Factory::GetInstance();
	f.registerComponent<Transform>();
	f.registerComponent<Mesh>();
	f.registerComponent<Light>();
	f.registerComponent<Camera>();
	f.registerComponent<RigidBody>();
	f.registerComponent<Collider>();
	f.registerComponent<AudioListener>();
	f.registerComponent<Animator>();
	f.registerComponent<AudioSource>();
	f.registerComponent<ParticleSystem>();
	f.registerComponent<Billboard>();
	f.registerComponent<TestComponent>();
}


int main(int argc, char* argv[]) {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	factory();
	
	if (RenderManager::Init("Test FORGE") && AudioManager::Init() && SceneManager::Init() && Input::Init()){

		LoadManager* loadManager = new LoadManager("Assets/assets.forge.lua", "scenetest.lua");
		RenderManager& render = *RenderManager::GetInstance();
		SceneManager& sceneManager = *SceneManager::GetInstance();
		PhysicsManager& phyisicsManager = *PhysicsManager::GetInstance();
		phyisicsManager.initPhysics();

		Input& input = *Input::GetInstance();
		AudioManager& ad = *AudioManager::GetInstance();
		sceneManager.changeScene("Test");

		double deltaTime = 0;
		double fixedUpdateTimer = 0;

		while (!input.keyUp(K_ESC)) {
			double start = SDL_GetTicks();
		    input.refresh();
		    input.update();
		    if (!sceneManager.update()) {
					break;
				}
			sceneManager.refresh();
			ad.update();
		    if(!render.render())
				break;
			else {
				if (phyisicsManager.isDebugModeEnabled())
					phyisicsManager.drawDebug();
			}

			double end = SDL_GetTicks();
			deltaTime = end - start;

			fixedUpdateTimer += deltaTime;

			while (fixedUpdateTimer >= FIXED_UPDATE_RATE) {
				sceneManager.fixedUpdate();
				phyisicsManager.updatePhysics();
				fixedUpdateTimer -= FIXED_UPDATE_RATE;
			}
		}
		sceneManager.cleanUp();
		delete loadManager;
	}

	//delete render.getInstance();
	return 0;
}
