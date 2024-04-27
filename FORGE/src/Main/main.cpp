#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <cstdio>
#endif

#include "MainForge.h"
#include "ForgeError.h"

#ifdef _DEBUG
#define closeWithError(message) reportError(message); std::cout << "Pulsa cualquier tecla para continuar.\n"; static_cast<int>(std::getchar()); return EXIT_FAILURE
#else
#define closeWithError(message) return EXIT_FAILURE
#endif

int main(int argc, char* argv[]) {
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
	std::string configFile = "config.forge.lua";
	if (argc > 2) {
		closeWithError("Se proporcionaron demasiados argumentos, el unico argumento opcional es la ruta del archivo de configuracion.");
	}
	if (argc > 1) {
		configFile = argv[1];
	}
	if (!MainForge::Init(configFile)) {
		MainForge::ShutDown();
		closeWithError("Hubo un fallo en la inicializacion.");
	}
	if (!MainForge::MainLoop()) {
		MainForge::ShutDown();
		closeWithError("Hubo un fallo en la ejecucion.");
	}
	if (!MainForge::ShutDown()) {
		closeWithError("Hubo un fallo en el cierre.");
	}
	return EXIT_SUCCESS;
}