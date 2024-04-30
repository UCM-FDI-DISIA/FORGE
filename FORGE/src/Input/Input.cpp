#include "Input.h"
#include <SDL.h>

std::unique_ptr<Input> Input::instance = nullptr;
bool Input::initialized = false;

void Input::onMouseMotion(const SDL_Event& event) {
	mousePos.set(static_cast<float>(event.motion.x), static_cast<float>(event.motion.y));
}

void Input::onMouseWheelMotion(const SDL_Event& event) {
	if (event.wheel.y == 1) {
		mouseWheelUp = true;
	}
	else if (event.wheel.y == -1) {
		mouseWheelDown = true;
	}
}

void Input::onMouseButton(const SDL_Event& event, bool down) {
	switch (event.button.button)
	{
		case SDL_BUTTON_LEFT:
			mouseButtons[0] = down;
			break;
		case SDL_BUTTON_MIDDLE:
			mouseButtons[1] = down;

			break;
		case SDL_BUTTON_RIGHT:
			mouseButtons[2] = down;
			break;
		default:
			break;
	}
}

bool Input::controllerButtonDownEvent() {
	return isControllerButtonDownEvent;
}

bool Input::controllerButtonUpEvent() {
	return isControllerButtonUpEvent;
}

bool Input::controllerAxisMotionEvent() {
	return isControllerAxisMotionEvent;
}

void Input::onControllerDeviceAdded() {
	if (controller == nullptr) {
		controller = SDL_GameControllerOpen(0);
		isControllerDeviceAddedEvent = true;
	}
}
void Input::onControllerDeviceRemoved() {
	if (controller != nullptr) {
		SDL_GameControllerClose(controller);
		controller = nullptr;
		isControllerDeviceRemovedEvent = true;
	}
}

bool Input::controllerDeviceAddedEvent() {
	return isControllerDeviceAddedEvent;
}

bool Input::controllerDeviceRemovedEvent() {
	return isControllerDeviceRemovedEvent;
}

void Input::onControllerButtonDown(const SDL_Event& event) {
	isControllerButtonDownEvent = true;
}
void Input::onControllerButtonUp(const SDL_Event& event) {
	isControllerButtonUpEvent = true;
}
void Input::onControllerAxisMotion(const SDL_Event& event) {
	isControllerAxisMotionEvent = true;
}
void Input::onWindowEvent(const SDL_Event& event) {
	switch (event.window.event) {
		case SDL_WINDOWEVENT_CLOSE:
			onWindowClose();
			break;
		default:
			break;
	}
}
void Input::onWindowClose() {
	isWindowCloseEvent = true;
}


Input::Input() :
	#define UINT(SCNCD) static_cast<unsigned int>(SCNCD)
	SCANCODE {
		UINT(SDL_SCANCODE_ESCAPE), UINT(SDL_SCANCODE_F1), UINT(SDL_SCANCODE_F2), UINT(SDL_SCANCODE_F3), UINT(SDL_SCANCODE_F4),
		UINT(SDL_SCANCODE_F5), UINT(SDL_SCANCODE_F6), UINT(SDL_SCANCODE_F7), UINT(SDL_SCANCODE_F8), UINT(SDL_SCANCODE_F9),
		UINT(SDL_SCANCODE_F10), UINT(SDL_SCANCODE_F11), UINT(SDL_SCANCODE_F12), UINT(SDL_SCANCODE_1), UINT(SDL_SCANCODE_2),
		UINT(SDL_SCANCODE_3), UINT(SDL_SCANCODE_4), UINT(SDL_SCANCODE_5), UINT(SDL_SCANCODE_6), UINT(SDL_SCANCODE_7),
		UINT(SDL_SCANCODE_8), UINT(SDL_SCANCODE_9), UINT(SDL_SCANCODE_0), UINT(SDL_SCANCODE_BACKSPACE), UINT(SDL_SCANCODE_TAB),
		UINT(SDL_SCANCODE_Q), UINT(SDL_SCANCODE_W), UINT(SDL_SCANCODE_E), UINT(SDL_SCANCODE_R), UINT(SDL_SCANCODE_T),
		UINT(SDL_SCANCODE_Y), UINT(SDL_SCANCODE_U), UINT(SDL_SCANCODE_I), UINT(SDL_SCANCODE_O), UINT(SDL_SCANCODE_P),
		UINT(SDL_SCANCODE_CAPSLOCK), UINT(SDL_SCANCODE_A), UINT(SDL_SCANCODE_S), UINT(SDL_SCANCODE_D), UINT(SDL_SCANCODE_F),
		UINT(SDL_SCANCODE_G), UINT(SDL_SCANCODE_H), UINT(SDL_SCANCODE_J), UINT(SDL_SCANCODE_K), UINT(SDL_SCANCODE_L),
		UINT(SDL_SCANCODE_RETURN), UINT(SDL_SCANCODE_LSHIFT), UINT(SDL_SCANCODE_Z), UINT(SDL_SCANCODE_X), UINT(SDL_SCANCODE_C),
		UINT(SDL_SCANCODE_V), UINT(SDL_SCANCODE_B), UINT(SDL_SCANCODE_N), UINT(SDL_SCANCODE_M), UINT(SDL_SCANCODE_LCTRL),
		UINT(SDL_SCANCODE_LGUI), UINT(SDL_SCANCODE_LALT), UINT(SDL_SCANCODE_SPACE), UINT(SDL_SCANCODE_LEFT), UINT(SDL_SCANCODE_UP),
		UINT(SDL_SCANCODE_DOWN), UINT(SDL_SCANCODE_RIGHT) },
	#undef UINT
	keyboardState(SDL_GetKeyboardState(0)) {
	setDefaultState();
}

bool Input::Init() {
	try {
		instance = std::unique_ptr<Input>(new Input());
		initialized = true;
		SDL_GameControllerAddMappingsFromFile("gamecontrollerdb.txt");
		return true;
	}
	catch (std::exception e) {

		return false;
	}
}

Input* Input::GetInstance() {
	if (initialized) return instance.get();
	return nullptr;
}

void Input::update() {	
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type)
		{
			case SDL_MOUSEWHEEL:
				onMouseWheelMotion(event);
				break;
			case SDL_MOUSEMOTION:
				onMouseMotion(event);
				break;
			case SDL_MOUSEBUTTONDOWN:
				onMouseButton(event, true);
				break;
			case SDL_MOUSEBUTTONUP:
				onMouseButton(event, false);
				break;
			case SDL_CONTROLLERDEVICEADDED:
				onControllerDeviceAdded();
				break;
			case SDL_CONTROLLERDEVICEREMOVED:
				onControllerDeviceRemoved();
				break;
			case SDL_CONTROLLERBUTTONDOWN:
				onControllerButtonDown(event);
				break;
			case SDL_CONTROLLERBUTTONUP:
				onControllerButtonUp(event);
				break;
			case SDL_CONTROLLERAXISMOTION:
				onControllerAxisMotion(event);
				break;
			case SDL_WINDOWEVENT:
				onWindowEvent(event);
				break;
			default: 
				break;
		}
	}
}

void Input::refresh() {
	for (auto& key : keys) {
		key.second = keyboardState[SCANCODE[key.first]];
	}

	setDefaultState();
}

void Input::setDefaultState() {
	mouseWheelUp = false;
	mouseWheelDown = false;

	isControllerDeviceAddedEvent = false;
	isControllerDeviceRemovedEvent = false;
	isControllerButtonDownEvent = false;
	isControllerButtonUpEvent = false;
	isControllerAxisMotionEvent = false;
	isWindowCloseEvent = false;
}

bool Input::keyDown(KeyNames k) {
	if (keyboardState[SCANCODE[k]] && (!keys.count(k) || !keys[k])) {
		keys[k] = true;
		return true;
	}
	return false;
}

bool Input::keyPressed(KeyNames k) {
	if (keyboardState[SCANCODE[k]]) {
		if (!keys.count(k)) {
			keys[k] = true;
			return false;
		}
		else if (keys[k]) {
			return true;
		}
	}
	return false;
}

bool Input::keyUp(KeyNames k) {
	if (!keyboardState[SCANCODE[k]] && keys[k]) {
		keys[k] = false;
		return true;
	}
	return false;
}

forge::Vector2 Input::getMousePosition() {
	return mousePos;
}

bool Input::wheelUp() {
	return mouseWheelUp;
}

bool Input::wheelDown() {
	return mouseWheelDown;
}

bool Input::isMouseButtonPressed(MouseNames button) {
	return mouseButtons[button];
}

bool Input::isControllerButtonDown(ControllerButtonNames button) {
	return controllerButtonDownEvent() && SDL_GameControllerGetButton(controller, (SDL_GameControllerButton) button) == 1;
}

bool Input::isControllerButtonUp(ControllerButtonNames button) {
	return controllerButtonUpEvent() && SDL_GameControllerGetButton(controller, (SDL_GameControllerButton) button) == 0;
}

int Input::getControllerAxis(ControllerAxisNames ax) {
	int axis = SDL_GameControllerGetAxis(controller, (SDL_GameControllerAxis) ax);
	float deadZone = (axis >= 0) ? CONTROLLER_AXIS_POS_DEADZONE : CONTROLLER_AXIS_NEG_DEADZONE;
	float max = (axis >= 0) ? CONTROLLER_AXIS_MAX : CONTROLLER_AXIS_MIN;

	if (abs(axis) < abs(deadZone)) return 0;
	return static_cast<int>(axis - (deadZone * ((max - axis) / (max - deadZone))));
}

float Input::getNormalizedControllerAxis(ControllerAxisNames ax) {
	float axis = static_cast<float>(getControllerAxis(ax));
	return axis / abs((axis >= 0) ? CONTROLLER_AXIS_MAX : CONTROLLER_AXIS_MIN);
}

bool Input::isControllerConnected() {
	return controller != nullptr;
}

bool Input::isWindowClosed() {
	return isWindowCloseEvent;
}
