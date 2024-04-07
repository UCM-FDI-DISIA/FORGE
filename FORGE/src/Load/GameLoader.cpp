#include "GameLoader.h"

GameLoader::GameLoader() :
	hDLL(nullptr) {
}

bool GameLoader::init(std::string const& gameDll) {
	hDLL = LoadLibraryA(gameDll.c_str());
	return hDLL != NULL;
}

typedef void(CALLBACK* LPFNDLL_registerComponents)(Factory&);
bool GameLoader::registerComponents(Factory& f) {
	if (hDLL == nullptr) {
		return false;
	}

	LPFNDLL_registerComponents lpfnDll_registerComponents;

	lpfnDll_registerComponents = (LPFNDLL_registerComponents)GetProcAddress(hDLL, "registerComponents");
	if (lpfnDll_registerComponents != NULL) {
		lpfnDll_registerComponents(f);
		return true;
	}
	return false;
	
}

bool GameLoader::free() {
	bool res = FreeLibrary(hDLL) != 0;
	hDLL = nullptr;
	return res;
}
