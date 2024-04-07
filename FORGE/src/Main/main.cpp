#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif
#include <iostream>
#include "MainForge.h"

int main(int argc, char* argv[]) {
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
	std::string configFile = "Assets/config.forge.lua";
	if (argc > 1) {
		if (argc > 2) {
			std::cerr << "Se proporcionaron demasiados argumentos, el unico argumento opcional es la ruta del archivo de configuracion.\n";
			return EXIT_FAILURE;
		}
		configFile = argv[1];
	}
	if (!MainForge::Init(configFile)) {
		MainForge::ShutDown();
		return EXIT_FAILURE;
	}
	MainForge::MainLoop();
	MainForge::ShutDown();
	return EXIT_SUCCESS;
}