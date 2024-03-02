#include "Input.h"

int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	SDL_Init(SDL_INIT_EVERYTHING);
	auto window = SDL_CreateWindow("Prueba", 100, 100, 900, 600, SDL_WINDOW_SHOWN);
	Input* input = Input::getInstance();
	SDL_Event SDLevent;

	bool end = false;
	while (!end) {     
		input->update();

		// RATON
		//std::pair<int, int> mPos = input->getMousePosition();
		//std::cout << "(" << mPos.first << ", " << mPos.second << ")\n";
		if (input->wheelUp()) std::cout << "rueda arriba" << "\n";
		else if (input->wheelDown()) std::cout << "rueda abajo" << "\n";
		if (input->isMouseButtonPressed(B_LEFT)) std::cout << "izquierdo" << "\n";
		else if (input->isMouseButtonPressed(B_MIDDLE)) std::cout << "rueda" << "\n";
		else if (input->isMouseButtonPressed(B_RIGHT)) std::cout << "derecho" << "\n";

		// TECLAS
		input->keyDown(K_1);
		input->keyUp(K_1);
		input->keyPressed(K_1);
		input->keyPressed(K_2);
		input->keyDown(K_3);
		input->keyUp(K_4);
		if (input->keyDown(K_ESC)) end = true;


		input->refresh();
	}
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0; 
}