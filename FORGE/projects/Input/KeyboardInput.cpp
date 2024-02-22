#include <iostream>
#include "SDL.h"

int main() {
	char c = ' ';     
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_CreateWindow("Prueba", 100, 100, 900, 600, SDL_WINDOW_SHOWN);
	while (c == ' ') {
		SDL_Event SDLevent;         
		while (SDL_PollEvent(&SDLevent)) {
			if (SDLevent.type == SDL_KEYDOWN)
				std::cout << "Hey :)\n";         
		}        
	}      
	return 0; 
}