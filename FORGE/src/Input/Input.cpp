#include "Input.h"

std::unique_ptr<Input> Input::instance = nullptr;

void Input::onMouseMotion(const SDL_Event& event) {
	mousePos.first = event.motion.x;
	mousePos.second = event.motion.y;
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

Input::Input() {
	SDLPreviousEvent.type = SDL_KEYDOWN;
	keyboardState = SDL_GetKeyboardState(0);
	setDefaultState();
	SDL_GameControllerAddMappingsFromFile("gamecontrollerdb.txt");
}

Input* Input::getInstance() {
	if (instance.get() != nullptr) return instance.get();
	return (instance = std::unique_ptr<Input>(new Input())).get();
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
			default: 
				break;
		}
	}
}

void Input::refresh() {
	for (auto it = keys.begin(); it != keys.end(); ++it) {
		it->second = keyboardState[SCANCODE[it->first]];
	}

	setDefaultState();
}

void Input::setDefaultState() {
	mouseWheelUp = false;
	mouseWheelDown = false;

	for (int i = 0; i < 3; i++) {
		mouseButtons[i] = false;
	}

	isControllerDeviceAddedEvent = false;
	isControllerDeviceRemovedEvent = false;
	isControllerButtonDownEvent = false;
	isControllerButtonUpEvent = false;
	isControllerAxisMotionEvent = false;
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

std::pair<int, int> Input::getMousePosition() {
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
	float dz = (axis >= 0) ? CONTROLLER_AXIS_POS_DEADZONE : CONTROLLER_AXIS_NEG_DEADZONE;
	float max = (axis >= 0) ? CONTROLLER_AXIS_MAX : CONTROLLER_AXIS_MIN;

	if (abs(axis) < abs(dz)) return 0;
	return axis - (dz * ((max - axis) / (max - dz)));
}

float Input::getNormalizedControllerAxis(ControllerAxisNames ax) {
	float axis = getControllerAxis(ax);
	return axis / abs((axis >= 0) ? CONTROLLER_AXIS_MAX : CONTROLLER_AXIS_MIN);
}

bool Input::isControllerConnected() {
	return controller != nullptr;
}