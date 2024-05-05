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
std::function<void(void)> Button::mainFunc = nullptr;

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
	forge::Vector2 mousePosition = input->getMousePosition();

	if (mousePosition.getX() > transform->getPosition().getX() 
		&& mousePosition.getX() < transform->getPosition().getX() + transform->getScale().getX()
		&& mousePosition.getY() > transform->getPosition().getY()
		&& mousePosition.getY() < transform->getPosition().getY() + transform->getScale().getY()) {
		newState = forge::HOVER_STATE;
		if (input->isMouseButtonPressed(M_LEFT)) {
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
	if (newState == forge::CLICKED_STATE && state == forge::HOVER_STATE) {
		if (onClick != nullptr) {
			(*onClick)(*onClickInvoker);
		}
	}
	if (newState == forge::HOVER_STATE && state == forge::CLICKED_STATE) {
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
}

Button::Button() :
	Image(),
	clicked(false),
	onOver(nullptr),
	onClick(nullptr),
	onRelease(nullptr),
	onOverInvoker(nullptr),
	onClickInvoker(nullptr),
	onReleaseInvoker(nullptr),
	input(Input::GetInstance()),
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

	initInvoker(data, onOverInvoker, "onOverInvoker");
	initInvoker(data, onClickInvoker, "onClickInvoker");
	initInvoker(data, onReleaseInvoker, "onReleaseInvoker");

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
	//TODO : BORRAR TODAS LAS TEXTURAS
}

void Button::update() {
	// IDEA:
	// Comprobar si el raton esta dentro de los limites del boton llamando al InputManager.getMousePosition().
	// Si lo está, entonces setear la imagen de hover:
	// state = forge::HOVER; changeButtonImage()
	// Si no lo esta, entonces setear la imagen de idle:
	// state = forge::IDLE; changeButtonImage()
	// Si se presiona el raton a la vez que se esta en el estado de hover entonces hacer todo el tema de callbacks
	// que antes haciamos en el bucle principal del GUITest de la rama de UI asi:
	// Button::resetFunction(); button->update(); Button::mainFunctionCall(); - la idea deberia ser parecida
	// Para comprobar si se esta pulsando el raton: InputManager.isMouseButtonPressed(MouseNames button);
	// Los MouseNames estan en el .h del input
	checkMousePosition();
	checkCallbacks();
	if (state != newState) {
		state = newState;
		changeButtonImage();
	}
}

void Button::resetFunction() {
	mainFunc = nullptr;
}

bool Button::mainFunctionCall() {
	if (mainFunc == nullptr) return false;
	mainFunc();
	return true;
}

bool Button::isPressed() {
	return clicked;
}
