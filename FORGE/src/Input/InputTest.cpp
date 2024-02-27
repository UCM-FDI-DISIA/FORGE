#include "Input.h"

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
			
			input->KeyDown(KeyNames::K_1);
			//input->KeyUp(KeyNames::K_1);
			//input->KeyPressed(KeyNames::K_1);
			//input->KeyPressed(KeyNames::K_2);
			input->ControllerAxisMotion(SDLevent);
			input->ControllerButtonDown(SDLevent);
			if (controller == nullptr && SDLevent.type == SDL_CONTROLLERDEVICEADDED) {
				controller = SDL_GameControllerOpen(0);
			}
			input->update();
			if (c != ' ') std::cout << " '" << c << "'\n";
		}
	}      
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0; 
}