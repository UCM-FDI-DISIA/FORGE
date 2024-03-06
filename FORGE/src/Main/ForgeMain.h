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

	/// <summary>
	/// </summary>
	/// <returns>la instancia de ForgeMain</returns>
	static ForgeMain* getInstance();
	
	/// <summary>
	/// Inicializador de todos los modulos, a partir de un archivo de configuracion Lua.
	/// @TODO Especificar el formato del archivo de configuracion.
	/// </summary>
	/// <param name="LuaConfigPath">El camino al archivo de configuracion</param>
	void init(std::string LuaConfigPath);

	/// <summary>
	/// Inicializa el bucle principal del juego.
	/// </summary>
	void startMainLoop();

	
	
	/// <summary>
	/// Tiempo pasado desde el ultimo frame.
	/// </summary>
	static double deltaTime;

	/// <summary>
	/// Valor que indica si el bucle principal esta corriendo. Modificado por el resto de modulos para el cierre del programa.
	/// </summary>
	bool isRunning;
private:
	/// <summary>
	/// Instancia de ForgeMain, para el patron singleton.
	/// </summary>
	static ForgeMain* instance;

	/// <summary>
	/// Trata el cierre de todos los modulos.
	/// </summary>
	void manageModuleShutdowns();

	/// <summary>
	/// Constructor de la clase ForgeMain y de todos los modulos. Inicializa el bucle principal.
	/// </summary>
	ForgeMain();

	/// <summary>
	/// Destructor de la clase ForgeMain y de todos los modulos.
	/// </summary>
	~ForgeMain();

	//Forge::Render renderModule*;
	//Forge::Input inputModule*;
	//Forge::Physics physicsModule*;
	//Forge::Audio audioModule*;
	//Forge::Load loadModule*;
	//Forge::EC ECModule*;
	//Forge::GUI GUIModule*;

	/// <summary>
	/// Acumulador de tiempo para los fixed updates
	/// </summary>
	double fixedUpdateAccumulator;

	/// <summary>
	/// Controla el tiempo entre updates, y si ha pasado el tiempo suficiente, llama a fixedUpdate cuantas veces sea necesario.
	/// </summary>
	void manageFixedUpdates();
};

