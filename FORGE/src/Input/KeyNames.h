#pragma once

const int KEYNAMES_SIZE = 62;
const int BUTTONNAMES_SIZE = 3;

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