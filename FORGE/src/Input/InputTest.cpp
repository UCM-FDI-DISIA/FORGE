#include <iostream>
#include "SDL.h"
#include "Input.hpp"

int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	SDL_Init(SDL_INIT_EVERYTHING);
	auto window = SDL_CreateWindow("Prueba", 100, 100, 900, 600, SDL_WINDOW_SHOWN);
	Input* input = new Input();
	SDL_Event SDLevent;
	SDL_GameController* controller = nullptr;

	char c = ' ';
	while (c == ' ') {      
		while (SDL_PollEvent(&SDLevent)) {
			input->KeyDown(SDLevent);
			input->KeyUp(SDLevent);
			input->KeyDown(SDLevent);
			input->ControllerAxisMotion(SDLevent);
			input->ControllerButtonDown(SDLevent);
			if (controller == nullptr && SDLevent.type == SDL_CONTROLLERDEVICEADDED) {
				controller = SDL_GameControllerOpen(0);
			}
			if (c != ' ') std::cout << " '" << c << "'\n";
		}
	}      
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0; 
}