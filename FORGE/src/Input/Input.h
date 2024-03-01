#pragma once

#include <iostream>
#include <unordered_map>
#include <array>
#include <memory>
#include "SDL.h"
#include "KeyNames.h"

#define CONTROLLER_AXIS_MAX 32767.0f
#define CONTROLLER_AXIS_MIN -32768.0f
#define CONTROLLER_AXIS_POS_DEADZONE (CONTROLLER_AXIS_MAX * 0.3f)
#define CONTROLLER_AXIS_NEG_DEADZONE (CONTROLLER_AXIS_MIN * 0.3f)

class Input {
private:
	static std::unique_ptr<Input> instance;

	SDL_Event SDLPreviousEvent;
	const Uint8* keyboardState;
	// true -> presionada/mantenida, false -> soltada
	std::unordered_map<KeyNames, bool> keys;

	std::pair<int, int> mousePos;
	bool mouseWheelUp;
	bool mouseWheelDown;
	std::array<bool, 3> mouseButtons;

	bool isControllerButtonDownEvent;
	bool isControllerButtonUpEvent;
	bool isControllerAxisMotionEvent;
	bool isControllerDeviceAddedEvent;
	bool isControllerDeviceRemovedEvent;

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

	SDL_GameController* controller;

public:
	/// <summary>
	/// Crea el gestor de entrada
	/// </summary>
	Input();

	/// <summary>
	/// Devuelve la instancia del input y, si no existe, la crea
	/// </summary>
	/// <returns>Instancia singleton del Input</returns>
	static Input* getInstance();

	/// <summary>
	/// Lee los eventos y llama a los metodos correspondientes de cada uno de ellos
	/// </summary>
	void update();

	/// <summary>
	/// Hace las operaciones necesarias tras un update para estar preparado para el siguiente
	/// </summary>
	void refresh();

	/// <summary>
	/// Devuelve al estado inicial (el estado por defecto) la estructura del gestor de input
	/// </summary>
	void setDefaultState();

	/// <summary>
	/// Devolver el caracter correspondiente a la tecla que se ha pulsado
	/// </summary>
	/// <param name="KeyNames">- tecla</param>
	/// <returns>Caracter de la tecla pulsada</returns>
	bool keyDown(KeyNames k);

	/// <summary>
	/// Devuelve el caracter correspondiente a la tecla que se esta manteniendo pulsada
	/// </summary>
	/// <param name="KeyNames">- tecla</param>
	/// <returns>Caracter de la tecla mantenida</returns>
	bool keyPressed(KeyNames k);

	/// <summary>
	/// Devuelve el caracter correspondiente a la tecla que se ha soltado
	/// </summary>
	/// <param name="KeyNames">- tecla</param>
	/// <returns>Carcater de la tecla</returns>
	bool keyUp(KeyNames k);

	/// <summary>
	/// Devuelve el caracter correspondiente a la boton del mando que se ha presionado
	/// </summary>
	/// <param name="SDLevent">- evento al que reaccionar</param>
	/// <returns>Carcater del boton</returns>
	char controllerButtonDown(const SDL_Event& SDLevent);

	/// <summary>
	/// Devuelve el caracter correspondiente a 
	/// </summary>
	/// <param name="SDLevent">- evento al que reaccionar</param>
	/// <returns>Caracter del movimiento</returns>
	char controllerAxisMotion(const SDL_Event& SDLevent);

	/// <summary>
	/// Guarda la posicion actual del raton
	/// </summary>
	/// <param name="SDLevent">- evento al que reaccionar</param>
	void onMouseMotion(const SDL_Event& event);

	/// <summary>
	/// Obtiene la posicion actual del raton
	/// </summary>
	/// <returns>first = x, second = y</returns>
	std::pair<int, int> getMousePosition();

	/// <summary>
	/// Detecta si la rueda se ha movido hacia arriba o hacia abajo
	/// </summary>
	/// <param name="SDLevent">- evento al que reaccionar</param>
	void onMouseWheelMotion(const SDL_Event& event);

	/// <summary>
	/// Devuelve si la rueda del raton se ha movido hacia arriba
	/// </summary>
	bool wheelUp();

	/// <summary>
	/// Devuelve si la rueda del raton se ha movido hacia abajo
	/// </summary>
	bool wheelDown();

	/// <summary>
	/// Marca en el array de los botones del raton si este se pulsa o se deja de pulsar
	/// </summary>
	/// <param name="SDLevent">- evento al que reaccionar</param>
	/// <param name="down">- 'true' si esta siendo pulsado, 'false' si no</param>
	void onMouseButton(const SDL_Event& event, bool down);

	/// <summary>
	/// Devuelve si el boton del raton indicado se esta pulsando
	/// </summary>
	/// <param name="button">- indice del boton del raton</param>
	bool isMouseButtonPressed(int button);

	/// <summary>
	/// Evento de boton de mando presionado
	/// </summary>
	bool controllerButtonDownEvent();

	/// <summary>
	/// Evento de boton de mando levantado
	/// </summary>
	bool controllerButtonUpEvent();

	/// <summary>
	/// Evento de joystick de mando movido
	/// </summary>
	bool controllerAxisMotionEvent();

	/// <summary>
	/// Comprobacion de boton de mando presionado
	/// </summary>
	/// <returns>Booleano correspondiente al resultado</returns>
	bool isControllerButtonDown(SDL_GameControllerButton button);

	/// <summary>
	/// Comprobacion de boton de mando presionado
	/// </summary>
	/// <returns>Booleano correspondiente al resultado</returns>
	bool isControllerButtonUp(SDL_GameControllerButton button);

	/// <summary>
	/// Devuelve el valor del eje del joystick del mando
	/// </summary>
	int getControllerAxis(SDL_GameControllerAxis ax);

	/// <summary>
	/// Devuelve el valor normalizado del eje del joystick del mando
	/// </summary>
	/// <returns>Valor normalizado del eje</returns>
	float getNormalizedControllerAxis(SDL_GameControllerAxis ax);

	/// <summary>
	/// Comprueba si hay un mando conectado
	/// </summary>
	bool isControllerConnected();
	
	/// <summary>
	/// Evento de mando añadido
	/// </summary>
	bool controllerDeviceAddedEvent();

	/// <summary>
	/// Evento de mando quitado
	/// </summary>
	bool controllerDeviceRemovedEvent();

	/// <summary>
	/// Añade un nuevo mando
	/// </summary>
	void onControllerDeviceAdded();

	/// <summary>
	/// Quita un mando
	/// </summary>
	void onControllerDeviceRemoved();

	/// <summary>
	/// Cambia el evento de Button Down a true
	/// </summary>
	void onControllerButtonDown(const SDL_Event& event);

	/// <summary>
	/// Cambia el evento de Button UP a true
	/// </summary>
	void onControllerButtonUp(const SDL_Event& event);

	/// <summary>
	/// Cambia el evento de Axis Motion a true
	/// </summary>
	void onControllerAxisMotion(const SDL_Event& event);
};