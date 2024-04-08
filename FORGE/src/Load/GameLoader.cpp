#include "GameLoader.h"
#include "ForgeError.h"

GameLoader::GameLoader() :
	hDLL(nullptr) {
}

bool GameLoader::init(std::string const& gameDll) {
	hDLL = LoadLibraryA(gameDll.c_str());
	if (hDLL == NULL) {
		throwError(false, "No se pudo cargar el juego, dll no encontrado o no valido.");
	}
	return true;
}

typedef void(CALLBACK* LPFNDLL_registerComponents)(Factory&);
bool GameLoader::registerComponents(Factory& factory) {
	if (hDLL == nullptr) {
		throwError(false, "No se pueden registrar los componentes porque no se ha cargado el juego.");
	}

	LPFNDLL_registerComponents lpfnDll_registerComponents;
	lpfnDll_registerComponents = (LPFNDLL_registerComponents)GetProcAddress(hDLL, "registerComponents");
	if (lpfnDll_registerComponents == NULL) {
		throwError(false, "No se pudo encontrar en el juego la funcion \"FORGE_IMPORT void registerComponents(Factory&)\".");
	}
	lpfnDll_registerComponents(factory);
	return true;
}

bool GameLoader::free() {
	if (FreeLibrary(hDLL) == 0) {
		throwError(false, "No se pudo cerrar la biblioteca del juego correctamente.");
	}
	hDLL = nullptr;
	return true;
}
