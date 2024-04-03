#include "GameLoad.h"

GameLoad::GameLoad() :
	hDLL(nullptr) {
}

bool GameLoad::init(std::string const& gameDll) {
	hDLL = LoadLibraryA(gameDll.c_str());
	return hDLL != NULL;
}

typedef void(CALLBACK* LPFNDLL_registerComponent)(Factory&);
bool GameLoad::registerComponents(Factory& f) {
	if (hDLL == nullptr) {
		return false;
	}

	LPFNDLL_registerComponent lpfnDll_registerComponents;

	lpfnDll_registerComponents = (LPFNDLL_registerComponent)GetProcAddress(hDLL, "registerComponents");
	if (lpfnDll_registerComponents != NULL) {
		lpfnDll_registerComponents(f);
		return true;
	}
	return false;
	
}

bool GameLoad::free() {
	bool res = FreeLibrary(hDLL) != 0;
	hDLL = nullptr;
	return res;
}
