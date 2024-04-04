#ifndef MAIN_FORGE_H_
#define MAIN_FORGE_H_
#include <string>
#include <memory>
namespace forge {
	class Time;
}
class Factory;
class RenderManager;
class SceneManager;
class AudioManager;
class LoadManager;
class Input;
class PhysicsManager;
//class UIManager;

class __declspec(dllexport) MainForge {
private:
	bool initialized;
	bool isRunning;
	bool finished;
	double fixedUpdateTimer;

	forge::Time& time;
	Factory& factory;
	RenderManager& renderManager;
	SceneManager& sceneManager;
	AudioManager& audioManager;
	LoadManager& loadManager;
	Input& inputManager;
	//PhysicsManager& physicsManager;
	//UIManager& uiManager;

	static std::unique_ptr<MainForge> instance;
	
	/// <summary>
	/// Guarda las referencias a todos los sistemas
	/// </summary>
	MainForge();
	//Al ser un singleton, no se puede copiar ni igualar
	MainForge(MainForge const&) = delete;
	void operator=(MainForge const&) = delete;

	/// <summary>
	/// Agrega todos los componentes internos del motor a la Factory
	/// </summary>
	void initFactory();
	/// <summary>
	/// Inicializador de todos los modulos, a partir de un archivo de configuracion
	/// </summary>
	/// <param name="luaConfigPath">El camino al archivo de configuracion</param>
	void init(std::string const& luaConfigPath);
	/// <summary>
	/// Controla el tiempo entre updates, y si ha pasado el tiempo suficiente, llama a fixedUpdate cuantas veces sea necesario
	/// </summary>
	void manageFixedUpdates();
	/// <summary>
	/// Actualiza los sistemas que lo necesiten
	/// </summary>
	void update();
	/// <summary>
	/// Muestra el juego en pantalla
	/// </summary>
	/// <return></return>
	bool render();
	/// <summary>
	/// Arranca el bucle principal del juego
	/// </summary>
	void mainLoop();
	/// <summary>
	/// Desactiva todos los sistemas
	/// </summary>
	void shutDown();

public:
	/// <summary>
	/// Inicializa el motor a partir de un archivo de configuracion
	/// </summary>
	/// <param name="luaConfigPath">La ruta al archivo de configuracion</param>
	static void Init(std::string const& luaConfigPath);
	/// <summary>
	/// Arranca el bucle principal del juego
	/// </summary>
	static void MainLoop();
	/// <summary>
	/// Detiene la ejecucion del bucle principal, saliendo del programa
	/// </summary>
	static void Exit();
	/// <summary>
	/// Vacia el objeto de MainForge
	/// </summary>
	static void ShutDown();
};

#endif // !MAIN_FORGE_H_