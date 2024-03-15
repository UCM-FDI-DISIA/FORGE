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
#include "AudioManager.h"
#include "Sound.h"

void factory() {
	Factory& f = *Factory::getInstance();
	f.registerComponent<Transform>();
	f.registerComponent<Mesh>();
	f.registerComponent<Light>();
	f.registerComponent<Camera>();
	f.registerComponent<TestMovement>();
}


int main(int argc, char* argv[]) {
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	factory();
	RenderManager& render = *RenderManager::getInstance();
    render.setup("Test FORGE");
	LuaForge* lf = new LuaForge();
	EcsLoad ecs("Assets/scenes/scenetest.lua", *lf);
    SceneManager& sceneManager = *SceneManager::getInstance();
    Input& input = *Input::getInstance();
	AudioManager* ad = new AudioManager();
    sceneManager.changeScene("Test");
	ad->addSound("Test", "Assets/sounds/AllObjectivesComp.wav");
    while (!input.keyUp(K_ESC)) {
        input.refresh();
        input.update();
        sceneManager.update();
		sceneManager.refresh();
        if(!render.render())
			break;
		if (input.keyDown(K_P)) {
			ad->getSound("Test")->play();
		}
    }
	delete ad;
	delete lf;
	sceneManager.cleanUp();

    return 0;
}

