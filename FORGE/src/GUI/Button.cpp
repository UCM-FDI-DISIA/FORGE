#include "Button.h"
#include "Serializer.h"
#include "GUIManager.h"
#include "Input.h"
#include "RectTransform.h"
#include "Image.h"
#include "ForgeFunction.h"
#include "Scene.h"
#include "Entity.h"
#include "Invoker.h"

const std::string Button::id = "Button";

void Button::changeButtonImage() {
	switch (state) {
		case forge::OUT_STATE:
			setMaterial(outTexture);
			break;
		case forge::HOVER_STATE:
			setMaterial(hoverTexture);
			break;
		case forge::CLICKED_STATE:
			setMaterial(clickedTexture);
			break;
	}
}

void Button::checkMousePosition() {
	forge::Vector2 const& mousePosition = input.getMousePosition();
	forge::Vector2 const& transformPos = transform->getPosition();
	forge::Vector2 const& transformScale = transform->getScale();

	if (mousePosition.getX() > transformPos.getX() 
		&& mousePosition.getX() < transformPos.getX() + transformScale.getX()
		&& mousePosition.getY() > transformPos.getY()
		&& mousePosition.getY() < transformPos.getY() + transformScale.getY()) {
		newState = forge::HOVER_STATE;
		if (input.isMouseButtonPressed(M_LEFT)) {
			newState = forge::CLICKED_STATE;
			clicked = true;
		}
	}
	else {
		newState = forge::OUT_STATE;
	}
}

void Button::checkCallbacks() {
	if (newState == forge::HOVER_STATE && state == forge::OUT_STATE) {
		if (onOver != nullptr) {
			(*onOver)(*onOverInvoker);
		}
	}
	else if (newState == forge::CLICKED_STATE && state == forge::HOVER_STATE) {
		if (onClick != nullptr) {
			(*onClick)(*onClickInvoker);
		}
	}
	else if (newState == forge::HOVER_STATE && state == forge::CLICKED_STATE) {
		if (onRelease != nullptr) {
			(*onRelease)(*onReleaseInvoker);
		}
	}
}

bool Button::initInvoker(ComponentData* data, Invoker*& invoker, std::string const& name) {
	if (data->has(name)) {
		std::string handler = data->get<std::string>(name);
		Entity* other = scene->getEntityByHandler(handler);
		if (other == nullptr) {
			throwError(false, "Invoker \"" << handler << "\" de Button::" << name << " no valido.");
		}
		invoker = &other->getInvoker();
	}
	else {
		invoker = &entity->getInvoker();
	}
	return true;
}

Button::Button() :
	clicked(false),
	onOver(nullptr),
	onClick(nullptr),
	onRelease(nullptr),
	onOverInvoker(nullptr),
	onClickInvoker(nullptr),
	onReleaseInvoker(nullptr),
	input(*Input::GetInstance()),
	state(forge::ButtonState::OUT_STATE),
	newState(forge::ButtonState::OUT_STATE),
	hoverTexture("default.png") {
	serializer(onOver, "onOver");
	serializer(onClick, "onClick");
	serializer(onRelease, "onRelease");
	serializer(outTexture, "out");
	serializer(hoverTexture, "hover");
	serializer(clickedTexture, "clicked");
}

Button::~Button() {
	if (onOver != nullptr) {
		delete onOver;
	}
	if (onClick != nullptr) {
		delete onClick;
	}
	if (onRelease != nullptr) {
		delete onRelease;
	}
}

bool Button::initComponent(ComponentData* data) {
	if (!Image::initComponent(data)) {
		return false;
	}
	setMaterial(outTexture);

	if (!initInvoker(data, onOverInvoker, "onOverInvoker")) {
		throwError(false, "onOverInvoker no valido");
	}
	if (!initInvoker(data, onClickInvoker, "onClickInvoker")) {
		throwError(false, "onClickInvoker no valido");
	}
	if (!initInvoker(data, onReleaseInvoker, "onReleaseInvoker")) {
		throwError(false, "onReleaseInvoker no valido");
	}

	return true;
}

void Button::onEnabled() {
	Image::onEnabled();
	state = forge::OUT_STATE;
	newState = forge::OUT_STATE;
	texture = outTexture;
	setMaterial(outTexture);
}

void Button::onDisabled() {
	Image::onDisabled();
	clicked = false;
}

void Button::update() {
	checkMousePosition();
	if (state != newState) {
		state = newState;
		changeButtonImage();
	}
	checkCallbacks();
}

bool Button::isPressed() const {
	return clicked;
}
