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
#include "RectTransform.h"
#include "Mesh.h"
#include "Light.h"
#include "Camera.h"
#include "TestComponent.h"
#include "Animator.h"
#include "ParticleSystem.h"
#include "Billboard.h"

#include "AudioManager.h"
#include "AudioListener.h"
#include "AudioSource.h"
#include "Sound.h"

#include "GUIManager.h"
#include "Image.h"
#include "Button.h"
#include "ImageButton.h"
#include "Text.h"
#include "InputText.h"

void factory() {
	Factory& f = *Factory::GetInstance();
	f.registerComponent<Transform>();
	f.registerComponent<RectTransform>();
	f.registerComponent<Mesh>();
	f.registerComponent<Light>();
	f.registerComponent<Camera>();
	f.registerComponent<TestComponent>();
	f.registerComponent<Animator>();
	f.registerComponent<ParticleSystem>();
	f.registerComponent<Billboard>();
	f.registerComponent<AudioSource>();
	f.registerComponent<AudioListener>();
	f.registerComponent<Image>();
	f.registerComponent<Button>();
	f.registerComponent<ImageButton>();
	f.registerComponent<Text>();
	f.registerComponent<InputText>();
}


int main(int argc, char* argv[]) {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	factory();
	if (RenderManager::Init("Test FORGE") && AudioManager::Init() && SceneManager::Init() && Input::Init()
		&& GUIManager::Init()) {
		LoadManager* loadManager = new LoadManager("Assets/assets.forge.lua", "scenetest.lua");
		//RenderManager& render = *RenderManager::GetInstance();
		SceneManager& sceneManager = *SceneManager::GetInstance();
		Input& input = *Input::GetInstance();
		AudioManager& ad = *AudioManager::GetInstance();
		GUIManager& gui = *GUIManager::GetInstance();
		gui.loadFont("Saeda", "Assets/fonts/LTSaeada-Black.otf", 16);
		sceneManager.changeScene("Test");
		while (!input.keyUp(K_ESC)) {
			input.refresh();
			input.update();
			gui.update();
			if (!sceneManager.update()) {
				break;
			}
			gui.render();
			sceneManager.refresh();
			ad.update();
			/*if (!render.render())
				break;*/
			gui.refresh();
		}
		sceneManager.cleanUp();
		delete loadManager;
	}

	return 0;
}
