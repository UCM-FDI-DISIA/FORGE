#ifndef MAIN_FORGE_H_
#define MAIN_FORGE_H_
#include <string>
#include <memory>
namespace forge {
	class Time;
}
class RenderManager;
class SceneManager;
class AudioManager;
class LoadManager;
class Input;
class PhysicsManager;
//class UIManager;

class MainForge {
private:
	Time& time;
	bool isRunning = true;
	double fixedUpdateTimer;

	RenderManager& renderManager;
	SceneManager& sceneManager;
	AudioManager& audioManager;
	//LoadManager& loadManager;
	Input& inputManager;
	//PhysicsManager& physicsManager;
	//UIManager& uiManager;

	static std::unique_ptr<MainForge> instance;
	
	/// <summary>
	/// Constructor de la clase ForgeMain y de todos los modulos. Inicializa el bucle principal.
	/// </summary>
	MainForge();
	/// <summary>
	/// Destructor de la clase ForgeMain y de todos los modulos.
	/// </summary>
	~MainForge();
	//Al ser un singleton, no se puede copiar ni igualar
	MainForge(MainForge const&) = delete;
	void operator=(MainForge const&) = delete;

	/// <summary>
	/// Controla el tiempo entre updates, y si ha pasado el tiempo suficiente, llama a fixedUpdate cuantas veces sea necesario.
	/// </summary>
	void manageFixedUpdates();

	void update();
	void refresh();
	bool render();

public:
	/// <summary>
	/// </summary>
	/// <returns>la instancia de ForgeMain</returns>
	static MainForge* getInstance();
	
	/// <summary>
	/// Inicializador de todos los modulos, a partir de un archivo de configuracion Lua.
	/// @TODO Especificar el formato del archivo de configuracion.
	/// </summary>
	/// <param name="luaConfigPath">El camino al archivo de configuracion</param>
	void init(std::string luaConfigPath);

	/// <summary>
	/// Inicializa el bucle principal del juego.
	/// </summary>
	void mainLoop();

	void exit();
};

#endif // !MAIN_FORGE_H_