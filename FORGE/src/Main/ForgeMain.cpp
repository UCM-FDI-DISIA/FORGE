#include "ForgeMain.h"

/*
a cambiar cuando se enlacen los modulos
#include "Render.h"
#include "Input.h"
#include "Physics.h"
#include "Audio.h"
#include "Load.h"
#include "EC.h"
#include "GUI.h"
*/

ForgeMain::ForgeMain()
{
	fixedUpdateAccumulator = 0;
	deltaTime = 0;

	//renderModule = new Forge::Render();
	//inputModule = new Forge::Input();
	//physicsModule = new Forge::Physics();
	//audioModule = new Forge::Audio();
	//loadModule = new Forge::Load();
	//ECModule = new Forge::EC();
	//GUIModule = new Forge::GUI();

	
}

ForgeMain* ForgeMain::getInstance()
{
	if (instance == nullptr)
	{
		instance = new ForgeMain();
	}
	return instance;
}

ForgeMain::~ForgeMain()
{
	//delete renderModule;
	//delete inputModule;
	//delete physicsModule;
	//delete audioModule;
	//delete loadModule;
	//delete ECModule;
	//delete GUIModule;
}

void ForgeMain::init(std::string LuaConfigPath)
{
	//inicializar todos los modulos
	//loadModule.init(LuaConfigPath);
	//renderModule.init();
	//inputModule.init();
	//physicsModule.init();
	//audioModule.init();
	//ECModule.init();
	//GUIModule.init();
}

void ForgeMain::startMainLoop()
{
	while (true /* !inputModule->exit */) //Desde Input?
	{
		manageFixedUpdates();
		double beforeFrame = 10; //Se checkearia el tiempo con SDL_GetCurrentTime o sucedaneo de Ogre
		//inputModule->update();
		//update();
		//render();
		//refresh();
		double afterFrame = 20; //Se checkearia el tiempo con SDL_GetCurrentTime o sucedaneo de Ogre
		deltaTime = afterFrame - beforeFrame; //Se podria guardar en una estructura de tiempo?
	}
}

void ForgeMain::manageFixedUpdates()
{
	fixedUpdateAccumulator += deltaTime;
	while (fixedUpdateAccumulator >= FIXED_UPDATE_RATE)
	{
		//ecsmodule->fixedUpdate();
		fixedUpdateAccumulator -= FIXED_UPDATE_RATE;
	}
}
