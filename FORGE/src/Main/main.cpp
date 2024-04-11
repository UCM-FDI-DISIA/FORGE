#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif
#include "MainForge.h"
#include "ForgeError.h"

int main(int argc, char* argv[]) {
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
	std::string configFile = "Assets/config.forge.lua";
	if (argc > 2) {
		throwError(EXIT_FAILURE, "Se proporcionaron demasiados argumentos, el unico argumento opcional es la ruta del archivo de configuracion.");
	}
	if (argc > 1) {
		configFile = argv[1];
	}
	if (!MainForge::Init(configFile)) {
		MainForge::ShutDown();
		throwError(EXIT_FAILURE, "Hubo un fallo en la inicializacion.");
	}
	MainForge::MainLoop();
	MainForge::ShutDown();
	return EXIT_SUCCESS;
}