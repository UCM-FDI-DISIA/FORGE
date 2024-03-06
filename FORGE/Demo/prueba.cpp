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


void factory() {
    Factory::getInstance()->registerComponent("Transform",
		[]()-> Component* {
			return new Transform();
		}
	);
    Factory::getInstance()->registerComponent("Mesh",
	[]()-> Component* {
		return new Mesh();
	}
	);
    Factory::getInstance()->registerComponent("Light",
	[]()-> Component* {
		return new Light();
	}
	);
    Factory::getInstance()->registerComponent("Camera",
	[]()-> Component* {
		return new Camera();
	}
	);
}

int main(int argc, char* argv[]) {
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	factory();
    LuaForge* lf = new LuaForge();
	EcsLoad ecs ("scenetest.lua", *lf);
    RenderManager& render = *RenderManager::getInstance();
    render.setup("Test FORGE");
    SceneManager& sceneManager = *SceneManager::getInstance();
    Input& input = *Input::getInstance();
    sceneManager.changeScene("Test");
    while (!input.keyUp(K_ESC)) {
        input.update();
        sceneManager.getScene("Test")->update();
        if(!render.render())
			break;
    }
    delete lf;
    return 0;
}

