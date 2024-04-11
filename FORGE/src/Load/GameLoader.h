#ifndef GAME_LOADER_H_
#define GAME_LOADER_H_
#include <string>
#include <Windows.h>
class Factory;

class GameLoader {
private:
	// Referencia a la DLL del juego
	HINSTANCE hDLL;
public:
	/// <summary>
	/// Crea el GameLoader sin inicializar
	/// </summary>
	GameLoader();
	/// <summary>
	/// Carga en el motor la DLL del juego
	/// </summary>
	/// <param name="gameDll">Nombre de la DLL del juego que se va a cargar</param>
	/// <returns>Booleano que indica si se ha podido enlazar el motor con la DLL del juego</returns>
	bool init(std::string const& gameDll);
	/// <summary>
	/// Llama a la funcion del juego que se encarga de registrar los componentes en el motor
	/// </summary>
	/// <param name="factory">Referencia a la Factory del motor para registrar los componentes</param>
	/// <returns>Booleano que indica si se ha podido llamar correctamente a la funcion implementada en el juego</returns>
	bool registerComponents(Factory& factory);
	/// <summary>
	/// Se encarga de cerrar la conexion del juego al motor
	/// </summary>
	/// <returns>Booleano que indica si se ha cerrado correctamente la conexion</returns>
	bool free();
};

#endif // !GAME_LOADER_H_