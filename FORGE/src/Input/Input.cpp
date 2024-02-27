#include "Input.h"
Input::Input() {
	SDLPreviousEvent.type = SDL_KEYDOWN;
	keyboardState = SDL_GetKeyboardState(0);
}

bool Input::KeyDown(KeyNames k) {
	if (keyboardState[SCANCODE[k]] && (!keys.count(k) || !keys[k])) {
		std::cout << "pulsada\n";
		keys[k] = true;
		return true;
	}
	return false;
}

bool Input::KeyPressed(KeyNames k) {
	if (keyboardState[SCANCODE[k]]) {
		if (!keys.count(k)) {
			keys[k] = true;
			return false;
		}
		else if (keys[k]) {
			std::cout << "mantenida: " << k << "\n";
			return true;
		}
	}
	return false;
}

bool Input::KeyUp(KeyNames k) {
	if (!keyboardState[SCANCODE[k]] && keys[k]) {
		std::cout << "soltada\n";
		keys[k] = false;
		return true;
	}
	return false;
}

char Input::ControllerButtonDown(SDL_Event SDLevent) {
	if (SDLevent.type == SDL_CONTROLLERBUTTONDOWN) {
		std::cout << "mando boton\n";
		SDLPreviousEvent.type = SDL_CONTROLLERBUTTONDOWN;
		return SDLevent.key.keysym.sym;
	}
	return ' ';
}

char Input::ControllerAxisMotion(SDL_Event SDLevent) {
	if (SDLevent.type == SDL_CONTROLLERAXISMOTION) {
		std::cout << "mando movimiento joystick\n";
		SDLPreviousEvent.type = SDL_CONTROLLERAXISMOTION;
		return SDLevent.key.keysym.sym;
	}
	return ' ';
}

void Input::update() {
	for (auto it = keys.begin(); it != keys.end(); ++it) {
		it->second = keyboardState[SCANCODE[it->first]];
	}
}