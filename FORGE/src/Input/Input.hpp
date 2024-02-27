#include "SDL.h"

#include <array>

class Input {
private:
	SDL_Event SDLPreviousEvent;

	const Uint8* keyboardState;

protected:

public:
	/// <summary>
	/// Creates the input manager
	/// </summary>
	Input() {
		SDLPreviousEvent.type = SDL_KEYUP;

		keyboardState = SDL_GetKeyboardState(0);
	}

	/// <summary>
	/// Returns the character corresponding to the key that has been pressed
	/// </summary>
	/// <param name="SDLevent">- event received to react to</param>
	/// <returns>Key character</returns>
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

	/// <summary>
	/// Returns the character corresponding to the key that is being pressed
	/// </summary>
	/// <param name="SDLevent">- event received to react to</param>
	/// <returns>Key character</returns>
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

	/// <summary>
	/// Returns the character corresponding to the key that has been released
	/// </summary>
	/// <param name="SDLevent">- event received to react to</param>
	/// <returns>Key character</returns>
	SDL_Keycode KeyUp(SDL_Event SDLevent) {
		if (SDLevent.type == SDL_KEYUP) {
			std::cout << "soltada\n";
			SDLPreviousEvent.type = SDL_KEYUP;
			std::cout << SDLevent.key.keysym.sym;
			return SDLevent.key.keysym.sym;
		}
		return ' ';
	}
	
	/// <summary>
	/// Returns the character corresponding to the controller button that has been pressed
	/// </summary>
	/// <param name="SDLevent">- event received to react to</param>
	/// <returns>Key character</returns>
	char ControllerButtonDown(SDL_Event SDLevent) {
		if (SDLevent.type == SDL_CONTROLLERBUTTONDOWN) {
			std::cout << "mando boton\n";
			SDLPreviousEvent.type = SDL_CONTROLLERBUTTONDOWN;
			return SDLevent.key.keysym.sym;
		}
		return ' ';
	}
	
	/// <summary>
	/// Returns the character corresponding to moving the joystick of the controller along an axis
	/// </summary>
	/// <param name="SDLevent">- event received to react to</param>
	/// <returns>Character of an axis movement</returns>
	char ControllerAxisMotion(SDL_Event SDLevent) {
		if (SDLevent.type == SDL_CONTROLLERAXISMOTION) {
			std::cout << "mando movimiento joystick\n";
			SDLPreviousEvent.type = SDL_CONTROLLERAXISMOTION;
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