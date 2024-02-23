#include <iostream>
#include "SDL.h"

int main() {
	char c = ' ';     
	SDL_Init(SDL_INIT_EVERYTHING);
	auto window = SDL_CreateWindow("Prueba", 100, 100, 900, 600, SDL_WINDOW_SHOWN);
	while (c == ' ') {
		SDL_Event SDLevent;         
		while (SDL_PollEvent(&SDLevent)) {
			if (SDLevent.type == SDL_KEYDOWN)
				std::cout << "Hey :)\n";         
		}        
	}      
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0; 
}