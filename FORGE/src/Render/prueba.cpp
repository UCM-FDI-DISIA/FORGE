// Este archivo es para que se suba la carpeta src/Render a Github
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include "OgreApp.h"

int main(int argc, char* argv[]) {
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    Render::OgreApp hola;
    hola.go();
    while (true)
    {
        if(!hola.getRoot()->renderOneFrame())
			break;
        if(hola.isClosed())
            break;
    }
    return 0;
}