#pragma once
#ifndef INPUT_H_
#define INPUT_H_

#include <memory>
#include <unordered_map>
#include <array>
#include "Vector2.h"

#define CONTROLLER_AXIS_MAX 32767.0f
#define CONTROLLER_AXIS_MIN -32768.0f
#define CONTROLLER_AXIS_POS_DEADZONE (CONTROLLER_AXIS_MAX * 0.3f)
#define CONTROLLER_AXIS_NEG_DEADZONE (CONTROLLER_AXIS_MIN * 0.3f)

const int KEYNAMES_SIZE = 62;

#pragma region predeclaraciones
union SDL_Event;
struct _SDL_GameController;
typedef struct _SDL_GameController SDL_GameController;
typedef unsigned char uint8_t;
typedef uint8_t Uint8;
#pragma endregion

/// <summary>
/// Nombres de las teclas desde fuera del motor.
/// Cada fila del teclado en una fila, si se quieren agregar teclas hacerlo por el final.
/// </summary>
enum KeyNames {
	K_ESC, K_F1, K_F2, K_F3, K_F4, K_F5, K_F6, K_F7, K_F8, K_F9, K_F10, K_F11, K_F12,
	K_1, K_2, K_3, K_4, K_5, K_6, K_7, K_8, K_9, K_0, K_RETURN,
	K_TAB, K_Q, K_W, K_E, K_R, K_T, K_Y, K_U, K_I, K_O, K_P,
	K_CAPS, K_A, K_S, K_D, K_F, K_G, K_H, K_J, K_K, K_L, K_ENTER,
	K_SHIFT, K_Z, K_X, K_C, K_V, K_B, K_N, K_M,
	K_CTRL, K_CONTEXT, K_ALT, K_SPACE, K_LEFT, K_UP, K_DOWN, K_RIGHT
};

/// <summary>
/// Nombres de los botones del raton desde fuera del motor
/// </summary>
enum MouseNames {
	M_LEFT, M_MIDDLE, M_RIGHT
};

/// <summary>
/// Nombres de los botones del mando desde fuera del motor
/// </summary>
enum ControllerButtonNames {
	C_BUTTON_INVALID = -1,
	C_BUTTON_A, C_BUTTON_B, C_BUTTON_X, C_BUTTON_Y,
	C_BUTTON_BACK, C_BUTTON_GUIDE, C_BUTTON_START,
	C_BUTTON_LEFTSTICK, C_BUTTON_RIGHTSTICK,
	C_BUTTON_LEFT_SHOULDER, C_BUTTON_RIGHT_SHOULDER,
	C_BUTTON_DPAD_UP, C_BUTTON_DPAD_DOWN, C_BUTTON_DPAD_LEFT, C_BUTTON_DPAD_RIGHT,
	C_BUTTON_MISC1,    /* Xbox Series X share button, PS5 microphone button, Nintendo Switch Pro capture button, Amazon Luna microphone button */
	C_BUTTON_PADDLE1,  /* Xbox Elite paddle P1 (upper left, facing the back) */
	C_BUTTON_PADDLE2,  /* Xbox Elite paddle P3 (upper right, facing the back) */
	C_BUTTON_PADDLE3,  /* Xbox Elite paddle P2 (lower left, facing the back) */
	C_BUTTON_PADDLE4,  /* Xbox Elite paddle P4 (lower right, facing the back) */
	C_BUTTON_TOUCHPAD, /* PS4/PS5 touchpad button */
	C_BUTTON_MAX
};

/// <summary>
/// Nombres de los ejes del mando desde fuera del motor
/// </summary>
enum ControllerAxisNames {
	C_AXIX_INVALID = -1,
	C_AXIS_LEFTX, C_AXIS_LEFTY,
	C_AXIS_RIGHTX, C_AXIS_RIGHTY,
	C_AXIS_TRIGGERLEFT, C_AXIS_TRIGGERRIGHT,
	C_AXIS_MAX
};

class Input {
private:
	static std::unique_ptr<Input> instance;
	static bool initialised;
	/// <summary>
	/// Array dinamico que proporciona SDL con el estado de cada tecla. Si kS[key] es 1 entonces esta siendo pulsada,
	/// de lo contrario sera 0
	/// </summary>
	const Uint8* keyboardState;
	/// <summary>
	/// Mapa con el estado previo de cada tecla. Si esta siendo presionada o mantenida entonces el valor es true, mientras
	/// que si ha sido soltada el valor es false 
	/// </summary>
	std::unordered_map<KeyNames, bool> keys;

	forge::Vector2 mousePos;
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
	const unsigned int SCANCODE[KEYNAMES_SIZE];

	SDL_GameController* controller;

	/// <summary>
	/// Guarda la posicion actual del raton
	/// </summary>
	/// <param name="event">Evento al que reaccionar</param>
	void onMouseMotion(const SDL_Event& event);

	/// <summary>
	/// Detecta si la rueda se ha movido hacia arriba o hacia abajo
	/// </summary>
	/// <param name="event">Evento al que reaccionar</param>
	void onMouseWheelMotion(const SDL_Event& event);

	/// <summary>
	/// Marca en el array de los botones del raton si este se pulsa o se deja de pulsar
	/// </summary>
	/// <param name="event">Evento al que reaccionar</param>
	/// <param name="down">Sera 'true' si esta siendo pulsado, 'false' si no</param>
	void onMouseButton(const SDL_Event& event, bool down);

	/// <summary>
	/// Evento de boton de mando presionado
	/// </summary>
	/// <returns>El estado del evento</returns>
	bool controllerButtonDownEvent();

	/// <summary>
	/// Evento de boton de mando levantado
	/// </summary>
	/// <returns>El estado del evento</returns>
	bool controllerButtonUpEvent();

	/// <summary>
	/// AGUIManagerade un nuevo mando
	/// </summary>
	void onControllerDeviceAdded();

	/// <summary>
	/// Quita un mando
	/// </summary>
	void onControllerDeviceRemoved();

	/// <summary>
	/// Evento de mando anadido
	/// </summary>
	/// <returns>El estado del evento</returns>
	bool controllerDeviceAddedEvent();

	/// <summary>
	/// Evento de mando quitado
	/// </summary>
	/// <returns>El estado del evento</returns>
	bool controllerDeviceRemovedEvent();

	/// <summary>
	/// Cambia el evento de Button Down a true
	/// </summary>
	/// <param name="event">Evento al que reaccionar</param>
	void onControllerButtonDown(const SDL_Event& event);

	/// <summary>
	/// Cambia el evento de Button UP a true
	/// </summary>
	/// <param name="event">Evento al que reaccionar</param>
	void onControllerButtonUp(const SDL_Event& event);

	/// <summary>
	/// Cambia el evento de Axis Motion a true
	/// </summary>
	/// <param name="event">Evento al que reaccionar</param>
	void onControllerAxisMotion(const SDL_Event& event);

	/// <summary>
	/// Evento de joystick de mando movido
	/// </summary>
	/// <returns>El estado del evento</returns>
	bool controllerAxisMotionEvent();
	
public:
	/// <summary>
	/// Crea el gestor de entrada
	/// </summary>
	Input();

	/// <summary>
	/// Crea una instancia del input
	/// </summary>
	/// <returns></returns>
	static bool Init();

	/// <summary>
	/// Devuelve la instancia del input y, si no existe, la crea
	/// </summary>
	/// <returns>Instancia singleton del Input</returns>
	static Input* GetInstance();

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
	/// Devuelve si se ha pulsado la tecla correspondiente
	/// </summary>
	/// <param name="k">Tecla a comprobar</param>
	bool keyDown(KeyNames k);

	/// <summary>
	/// Devuelve si se esta manteniendo la tecla correspondiente
	/// </summary>
	/// <param name="k">Tecla a comprobar</param>
	bool keyPressed(KeyNames k);

	/// <summary>
	/// Devuelve si se ha soltado la tecla correspondiente
	/// </summary>
	/// <param name="k">Tecla a comprobar</param>
	bool keyUp(KeyNames k);

	/// <summary>
	/// Obtiene la posicion actual del raton
	/// </summary>
	/// <returns>first = x, second = y</returns>
	forge::Vector2 getMousePosition();

	/// <summary>
	/// Devuelve si la rueda del raton se ha movido hacia arriba
	/// </summary>
	bool wheelUp();

	/// <summary>
	/// Devuelve si la rueda del raton se ha movido hacia abajo
	/// </summary>
	bool wheelDown();

	/// <summary>
	/// Devuelve si el boton del raton indicado se esta pulsando
	/// </summary>
	/// <param name="button">- indice del boton del raton</param>
	bool isMouseButtonPressed(MouseNames button);

	/// <summary>
	/// Devuelve si se ha pulsado el boton del mando
	/// </summary>
	/// <param name="button">Indice del boton del mando</param>
	bool isControllerButtonDown(ControllerButtonNames button);

	/// <summary>
	/// Devuelve si se ha soltado el boton del mando
	/// </summary>
	/// <param name="button">Indice del boton del mando</param>
	bool isControllerButtonUp(ControllerButtonNames button);

	/// <summary>
	/// Devuelve el valor del eje del joystick del mando
	/// </summary>
	/// <param name="ax">Eje del mando</param>
	int getControllerAxis(ControllerAxisNames ax);

	/// <summary>
	/// Devuelve el valor normalizado del eje del joystick del mando
	/// </summary>
	/// <param name="ax">Eje del mando</param>
	float getNormalizedControllerAxis(ControllerAxisNames ax);

	/// <summary>
	/// Devuelve si hay un mando conectado
	/// </summary>
	bool isControllerConnected();
};
#endif // !INPUT_H_