#include <iostream>
#include "SDL.h"
#include "Input.hpp"

int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	char c = ' ';     
	SDL_Init(SDL_INIT_EVERYTHING);
	auto window = SDL_CreateWindow("Prueba", 100, 100, 900, 600, SDL_WINDOW_SHOWN);
	Input* input = new Input();
	SDL_Event SDLevent;
	while (c == ' ') {      
		while (SDL_PollEvent(&SDLevent)) {
			//if (SDLevent.type = SDL_CONTROLLERBUTTONDOWN) std::cout << "AAAAAAA\n";
			//std::string st = input->KeyPressedS(SDLevent);
			input->KeyPressed(SDLevent);
			input->KeyUp(SDLevent);
			input->KeyDown(SDLevent);
		}        
	}      
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0; 
}