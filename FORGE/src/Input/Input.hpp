#include "SDL.h"
#include <array>
#include <unordered_map>
#include "KeyNames.h"

class Input {
private:
	SDL_Event SDLPreviousEvent;
	const Uint8* keyboardState;

	/// <summary>
	/// Traduccion de KeyNames a SDL_Scancodes, el numero es la cantidad de teclas mapeadas (constante de KeyNames.h).
	/// 5 Scancodes por linea, si se agregan mas hacerlo por el final.
	/// </summary>
	const SDL_Scancode SCANCODE[KEYNAMES_SIZE] =
	{
		{SDL_SCANCODE_ESCAPE},{SDL_SCANCODE_F1}, {SDL_SCANCODE_F2}, {SDL_SCANCODE_F3}, {SDL_SCANCODE_F4},
		{SDL_SCANCODE_F5},{SDL_SCANCODE_F6}, {SDL_SCANCODE_F7}, {SDL_SCANCODE_F8}, {SDL_SCANCODE_F9},
		{SDL_SCANCODE_F10}, {SDL_SCANCODE_F11},	{SDL_SCANCODE_F12}, {SDL_SCANCODE_1}, {SDL_SCANCODE_2},
		{SDL_SCANCODE_3}, {SDL_SCANCODE_4},	{SDL_SCANCODE_5},  {SDL_SCANCODE_6}, {SDL_SCANCODE_7},
		{SDL_SCANCODE_8}, {SDL_SCANCODE_9},	{SDL_SCANCODE_0},  {SDL_SCANCODE_BACKSPACE}, {SDL_SCANCODE_TAB},
		{SDL_SCANCODE_Q}, {SDL_SCANCODE_W},	{SDL_SCANCODE_E},  {SDL_SCANCODE_R}, {SDL_SCANCODE_T},
		{SDL_SCANCODE_Y}, {SDL_SCANCODE_U},	{SDL_SCANCODE_I},  {SDL_SCANCODE_O}, {SDL_SCANCODE_P},
		{SDL_SCANCODE_CAPSLOCK}, {SDL_SCANCODE_A},	{SDL_SCANCODE_S},  {SDL_SCANCODE_D}, {SDL_SCANCODE_F},
		{SDL_SCANCODE_G}, {SDL_SCANCODE_H},	{SDL_SCANCODE_J},  {SDL_SCANCODE_K}, {SDL_SCANCODE_L},
		{SDL_SCANCODE_RETURN}, {SDL_SCANCODE_LSHIFT}, {SDL_SCANCODE_Z},  {SDL_SCANCODE_X}, {SDL_SCANCODE_C},
		{SDL_SCANCODE_V}, {SDL_SCANCODE_B},	{SDL_SCANCODE_N},  {SDL_SCANCODE_M}, {SDL_SCANCODE_LCTRL},
		{SDL_SCANCODE_LGUI}, {SDL_SCANCODE_LALT},	{SDL_SCANCODE_SPACE},  {SDL_SCANCODE_LEFT}, {SDL_SCANCODE_UP},
		{SDL_SCANCODE_DOWN}, {SDL_SCANCODE_RIGHT}
	};
public:
	

	// true -> presionada/mantenida false -> soltada
	std::unordered_map<KeyNames, bool> keys;

//public:
	/// <summary>
	/// Nombres de las teclas desde fuera del motor.
	/// Cada fila del teclado en una fila, si se quieren agregar teclas hacerlo por el final.
	/// </summary>
	

	/// <summary>
	/// Creates the input manager
	/// </summary>
	Input() {
		SDLPreviousEvent.type = SDL_KEYDOWN;
		keyboardState = SDL_GetKeyboardState(0);
	}

	/// <summary>
/// Returns the character corresponding to the key that has been pressed
/// </summary>
/// <param name="SDLevent">- event received to react to</param>
/// <returns>Key character</returns>
	bool KeyDown(KeyNames k) {
		if (keyboardState[SCANCODE[k]] && (!keys.count(k) || !keys[k])) {
			std::cout << "pulsada\n";
			keys[k] = true;
			return true;
		}
		return false;
	}

	/// <summary>
	/// Returns the character corresponding to the key that is being pressed
	/// </summary>
	/// <param name="SDLevent">- event received to react to</param>
	/// <returns>Key character</returns>
	bool KeyPressed(KeyNames k) {
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

	/// <summary>
	/// Returns the character corresponding to the key that has been released
	/// </summary>
	/// <param name="SDLevent">- event received to react to</param>
	/// <returns>Key character</returns>
	bool KeyUp(KeyNames k) {
		if (!keyboardState[SCANCODE[k]] && keys[k]) {
			std::cout << "soltada\n";
			keys[k] = false;
			return true;
		}
		return false;
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

	/// <summary>
	/// Actualiza los eventos de tecla dentro del map
	/// </summary>
	void update() {
		for (auto it = keys.begin(); it != keys.end(); ++it) {
			it->second = keyboardState[SCANCODE[it->first]];
		}
	}
};