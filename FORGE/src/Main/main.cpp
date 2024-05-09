#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <cstdio>
#endif

#include "MainForge.h"
#include "ForgeError.h"
#include <Windows.h>

#ifdef _DEBUG
#define closeWithError(message) reportError(message); std::cout << "Pulsa ENTER para continuar.\n"; static_cast<int>(std::getchar()); return EXIT_FAILURE
#else
#define closeWithError(message) return EXIT_FAILURE
#endif

#ifdef _DEBUG
int main(int argc, char* argv[]) {
#else
int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE prevInstance, LPSTR lpCmdLine, int nCmdShow) {
#endif

#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
	std::string configFile = "config.forge.lua";
#ifdef _DEBUG
	if (argc > 2) {
		closeWithError("Se proporcionaron demasiados argumentos, el unico argumento opcional es la ruta del archivo de configuracion.");
	}
	if (argc > 1) {
		configFile = argv[1];
	}
#endif
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