#include "Input.h"
#include <iostream>

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
		if (input->wheelUp()) std::cout << "rueda raton arriba" << "\n";
		else if (input->wheelDown()) std::cout << "rueda raton abajo" << "\n";
		if (input->isMouseButtonPressed(M_LEFT)) std::cout << "raton boton izquierdo" << "\n";
		else if (input->isMouseButtonPressed(M_MIDDLE)) std::cout << "rueda raton" << "\n";
		else if (input->isMouseButtonPressed(M_RIGHT)) std::cout << "raton boton derecho" << "\n";

		// TECLAS
		if (input->keyDown(K_1)) std::cout << "pulsada" << "\n";
		if (input->keyUp(K_2)) std::cout << "soltada" << "\n";
		if (input->keyPressed(K_3)) std::cout << "mantenida" << "\n";
		if (input->keyDown(K_ESC)) end = true;

		// MANDO
		if (input->isControllerButtonDown(C_BUTTON_A)) std::cout << "A" << "\n";
		else if (input->isControllerButtonDown(C_BUTTON_B)) std::cout << "B" << "\n";
		else if (input->isControllerButtonDown(C_BUTTON_X)) std::cout << "X" << "\n";
		else if (input->isControllerButtonDown(C_BUTTON_Y)) std::cout << "Y" << "\n";		
		else if (input->isControllerButtonDown(C_BUTTON_BACK)) std::cout << "compartir" << "\n";
		else if (input->isControllerButtonDown(C_BUTTON_GUIDE)) std::cout << "central" << "\n";
		else if (input->isControllerButtonDown(C_BUTTON_START)) std::cout << "start" << "\n";
		else if (input->isControllerButtonDown(C_BUTTON_LEFTSTICK)) std::cout << "joystick izquierda" << "\n";
		else if (input->isControllerButtonDown(C_BUTTON_RIGHTSTICK)) std::cout << "joystick derecha" << "\n";
		else if (input->isControllerButtonDown(C_BUTTON_LEFT_SHOULDER)) std::cout << "superior izquierda" << "\n";
		else if (input->isControllerButtonDown(C_BUTTON_RIGHT_SHOULDER)) std::cout << "superior derecha" << "\n";
		else if (input->isControllerButtonDown(C_BUTTON_DPAD_UP)) std::cout << "cruzeta arriba" << "\n";
		else if (input->isControllerButtonDown(C_BUTTON_DPAD_DOWN)) std::cout << "cruzeta abajo" << "\n";
		else if (input->isControllerButtonDown(C_BUTTON_DPAD_LEFT)) std::cout << "cruzeta izquierda" << "\n";
		else if (input->isControllerButtonDown(C_BUTTON_DPAD_RIGHT)) std::cout << "cruzeta derecha" << "\n";
		if (input->getNormalizedControllerAxis(C_AXIS_LEFTY) != 0) 
			std::cout << "Joystick Izq Y: " << input->getNormalizedControllerAxis(C_AXIS_LEFTY) << "\n";
		if (input->getNormalizedControllerAxis(C_AXIS_LEFTX) != 0) 
			std::cout << "Joystick Izq X: " << input->getNormalizedControllerAxis(C_AXIS_LEFTX) << "\n";
		if (input->getNormalizedControllerAxis(C_AXIS_RIGHTY) != 0)
			std::cout << "Joystick Der Y: " << input->getNormalizedControllerAxis(C_AXIS_RIGHTY) << "\n";
		if (input->getNormalizedControllerAxis(C_AXIS_RIGHTX) != 0)
			std::cout << "Joystick Der X: " << input->getNormalizedControllerAxis(C_AXIS_RIGHTX) << "\n";
		if (input->getNormalizedControllerAxis(C_AXIS_TRIGGERLEFT))
			std::cout << "Gatillo Izq: " << input->getNormalizedControllerAxis(C_AXIS_TRIGGERLEFT) << "\n";
		if (input->getNormalizedControllerAxis(C_AXIS_TRIGGERRIGHT))
			std::cout << "Gatillo Der: " << input->getNormalizedControllerAxis(C_AXIS_TRIGGERRIGHT) << "\n";

		input->refresh();
	}
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0; 
}