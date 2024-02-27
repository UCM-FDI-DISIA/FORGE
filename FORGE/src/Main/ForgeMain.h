#ifndef FORGE_MAIN

#endif // !FORGE_MAIN

#define FIXED_UPDATE_RATE 0.02

#include <string>

class ForgeMain
{
public:


	//Al ser un singleton, no se puede copiar ni igualar
	ForgeMain(ForgeMain const&) = delete;
	void operator=(ForgeMain const&) = delete;

	static ForgeMain* getInstance();
	

	void init(std::string LuaConfigPath);

	void startMainLoop();

	static double deltaTime;
private:


	static ForgeMain* instance;
	/// <summary>
	/// Constructor de la clase ForgeMain y de todos los modulos. Inicializa el bucle principal.
	/// </summary>
	ForgeMain();

	~ForgeMain();
	//Forge::Render renderModule*;
	//Forge::Input inputModule*;
	//Forge::Physics physicsModule*;
	//Forge::Audio audioModule*;
	//Forge::Load loadModule*;
	//Forge::EC ECModule*;
	//Forge::GUI GUIModule*;




	double fixedUpdateAccumulator;

	void manageFixedUpdates();
};

