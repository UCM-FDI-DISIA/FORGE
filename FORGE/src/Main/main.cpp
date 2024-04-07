#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

#include "MainForge.h"

int main(int argc, char* argv[]) {
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
	// TODO: quizas dar la opcion de proporcionar desde argv una ruta de configuracion alternativa
	MainForge::Init("Assets/config.forge.lua");
	MainForge::MainLoop();
	MainForge::ShutDown();
	return 0;
}