#include "Input.h"
#include <SDL.h>
#include "ForgeError.h"

#define CONTROLLER_AXIS_MAX 32767.0f
#define CONTROLLER_AXIS_MIN -32768.0f
#define CONTROLLER_AXIS_POS_DEADZONE (CONTROLLER_AXIS_MAX * 0.3f)
#define CONTROLLER_AXIS_NEG_DEADZONE (CONTROLLER_AXIS_MIN * 0.3f)

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
	switch (event.button.button) {
		case SDL_BUTTON_LEFT:
			mouseButtons[0] = down;
			break;
		case SDL_BUTTON_MIDDLE:
			mouseButtons[1] = down;
			break;
		case SDL_BUTTON_RIGHT:
			mouseButtons[2] = down;
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
		case SDL_WINDOWEVENT_RESIZED:
			onWindowResize();
			break;
	}
}

void Input::onWindowClose() {
	isWindowCloseEvent = true;
}

void Input::onWindowResize() {
	isWindowResizeEvent = true;
}

Input::Input() :
	#define UINTCAST(SCNCD) static_cast<unsigned int>(SCNCD)
	SCANCODE {
		UINTCAST(SDL_SCANCODE_ESCAPE), UINTCAST(SDL_SCANCODE_F1), UINTCAST(SDL_SCANCODE_F2), UINTCAST(SDL_SCANCODE_F3), UINTCAST(SDL_SCANCODE_F4),
		UINTCAST(SDL_SCANCODE_F5), UINTCAST(SDL_SCANCODE_F6), UINTCAST(SDL_SCANCODE_F7), UINTCAST(SDL_SCANCODE_F8), UINTCAST(SDL_SCANCODE_F9),
		UINTCAST(SDL_SCANCODE_F10), UINTCAST(SDL_SCANCODE_F11), UINTCAST(SDL_SCANCODE_F12), UINTCAST(SDL_SCANCODE_1), UINTCAST(SDL_SCANCODE_2),
		UINTCAST(SDL_SCANCODE_3), UINTCAST(SDL_SCANCODE_4), UINTCAST(SDL_SCANCODE_5), UINTCAST(SDL_SCANCODE_6), UINTCAST(SDL_SCANCODE_7),
		UINTCAST(SDL_SCANCODE_8), UINTCAST(SDL_SCANCODE_9), UINTCAST(SDL_SCANCODE_0), UINTCAST(SDL_SCANCODE_BACKSPACE), UINTCAST(SDL_SCANCODE_TAB),
		UINTCAST(SDL_SCANCODE_Q), UINTCAST(SDL_SCANCODE_W), UINTCAST(SDL_SCANCODE_E), UINTCAST(SDL_SCANCODE_R), UINTCAST(SDL_SCANCODE_T),
		UINTCAST(SDL_SCANCODE_Y), UINTCAST(SDL_SCANCODE_U), UINTCAST(SDL_SCANCODE_I), UINTCAST(SDL_SCANCODE_O), UINTCAST(SDL_SCANCODE_P),
		UINTCAST(SDL_SCANCODE_CAPSLOCK), UINTCAST(SDL_SCANCODE_A), UINTCAST(SDL_SCANCODE_S), UINTCAST(SDL_SCANCODE_D), UINTCAST(SDL_SCANCODE_F),
		UINTCAST(SDL_SCANCODE_G), UINTCAST(SDL_SCANCODE_H), UINTCAST(SDL_SCANCODE_J), UINTCAST(SDL_SCANCODE_K), UINTCAST(SDL_SCANCODE_L),
		UINTCAST(SDL_SCANCODE_RETURN), UINTCAST(SDL_SCANCODE_LSHIFT), UINTCAST(SDL_SCANCODE_Z), UINTCAST(SDL_SCANCODE_X), UINTCAST(SDL_SCANCODE_C),
		UINTCAST(SDL_SCANCODE_V), UINTCAST(SDL_SCANCODE_B), UINTCAST(SDL_SCANCODE_N), UINTCAST(SDL_SCANCODE_M), UINTCAST(SDL_SCANCODE_LCTRL),
		UINTCAST(SDL_SCANCODE_LGUI), UINTCAST(SDL_SCANCODE_LALT), UINTCAST(SDL_SCANCODE_SPACE), UINTCAST(SDL_SCANCODE_LEFT), UINTCAST(SDL_SCANCODE_UP),
		UINTCAST(SDL_SCANCODE_DOWN), UINTCAST(SDL_SCANCODE_RIGHT) },
	#undef UINTCAST
	keyboardState(SDL_GetKeyboardState(0)) {
	setDefaultState();
}

bool Input::Init() {
	if (initialized) {
		throwError(false, "Ya se habia inicializado el Input");
	}
	if(SDL_GameControllerAddMappingsFromFile("gamecontrollerdb.txt") == -1) {
		reportError("No se pudo cargar el mapeado de mandos en el Input");
	}
	instance = std::unique_ptr<Input>(new Input());
	initialized = true;
	return true;
}

Input* Input::GetInstance() {
	if (initialized) return instance.get();
	return nullptr;
}

void Input::update() {	
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
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
	isWindowResizeEvent = false;
}

bool Input::keyDown(KeyNames const& k) {
	if (keyboardState[SCANCODE[k]] && (!keys.count(k) || !keys[k])) {
		keys[k] = true;
		return true;
	}
	return false;
}

bool Input::keyPressed(KeyNames const& k) {
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

bool Input::keyUp(KeyNames const& k) {
	if (!keyboardState[SCANCODE[k]] && keys[k]) {
		keys[k] = false;
		return true;
	}
	return false;
}

forge::Vector2 const& Input::getMousePosition() {
	return mousePos;
}

bool Input::wheelUp() {
	return mouseWheelUp;
}

bool Input::wheelDown() {
	return mouseWheelDown;
}

bool Input::isMouseButtonPressed(MouseNames const& button) {
	return mouseButtons[button];
}

bool Input::isControllerButtonDown(ControllerButtonNames const& button) {
	return controllerButtonDownEvent() && SDL_GameControllerGetButton(controller, static_cast<SDL_GameControllerButton>(button)) == 1;
}

bool Input::isControllerButtonUp(ControllerButtonNames const& button) {
	return controllerButtonUpEvent() && SDL_GameControllerGetButton(controller, static_cast<SDL_GameControllerButton>(button)) == 0;
}

int Input::getControllerAxis(ControllerAxisNames const& ax) {
	int axis = SDL_GameControllerGetAxis(controller, static_cast<SDL_GameControllerAxis>(ax));
	float deadZone = (axis >= 0) ? CONTROLLER_AXIS_POS_DEADZONE : CONTROLLER_AXIS_NEG_DEADZONE;
	float max = (axis >= 0) ? CONTROLLER_AXIS_MAX : CONTROLLER_AXIS_MIN;

	if (abs(axis) < abs(deadZone)) {
		return 0;
	}
	return static_cast<int>(axis - (deadZone * ((max - axis) / (max - deadZone))));
}

float Input::getNormalizedControllerAxis(ControllerAxisNames const& ax) {
	float axis = static_cast<float>(getControllerAxis(ax));
	return axis / abs((axis >= 0) ? CONTROLLER_AXIS_MAX : CONTROLLER_AXIS_MIN);
}

bool Input::isControllerConnected() {
	return controller != nullptr;
}

bool Input::isWindowClosed() {
	return isWindowCloseEvent;
}

bool Input::isWindowResized() {
	return isWindowResizeEvent;
}