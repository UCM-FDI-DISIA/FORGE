#include "SDL.h"


class Input {
private:
	SDL_Event SDLPreviousEvent;
protected:

public:
	Input() {
		SDLPreviousEvent.type = SDL_KEYUP;
	}

	char KeyDown(SDL_Event SDLevent) {
		if (SDLPreviousEvent.type == SDL_KEYUP) {
			if (SDLevent.type == SDL_KEYDOWN) {
				std::cout << "pulsada\n";
				SDLPreviousEvent.type = SDL_KEYDOWN;
				return SDLevent.key.keysym.sym;
			}
		}
		return ' ';
	}

	char KeyPressed(SDL_Event SDLevent) {
		if (SDLPreviousEvent.type == SDL_KEYDOWN) {
			if (SDLevent.type == SDL_KEYDOWN) {
				std::cout << "mantenido\n";
				SDLPreviousEvent.type = SDL_KEYDOWN;
				return SDLevent.key.keysym.sym;
			}
		}
		return ' ';
	}

	char KeyUp(SDL_Event SDLevent) {
		if (SDLevent.type == SDL_KEYUP) {
			std::cout << "soltada\n";
			SDLPreviousEvent.type = SDL_KEYUP;
			return SDLevent.key.keysym.sym;
		}
		return ' ';
	}

	//std::string KeyPressedS(SDL_Event SDLevent) {
	//	if (SDLPreviousEvent.type == SDL_KEYDOWN) {
	//		if (SDLevent.type == SDL_KEYDOWN) {
	//			std::cout << "mantenido\n";
	//			SDLPreviousEvent.type = SDL_KEYDOWN;
	//			//std::cout << "KeyDown_" << (char)SDLevent.key.keysym.sym << "\n";
	//			char c = SDLevent.key.keysym.sym;
	//			return ("KeyDown_" + c);
	//		}
	//	}
	//	return "";
	//}
};