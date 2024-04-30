#include "Button.h"
#include "Serializer.h"
#include "GUIManager.h"
#include "Input.h"
#include "RectTransform.h"
#include "Image.h"

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
		};
	}
	else {
		newState = forge::OUT_STATE;
	}
}

Button::Button() :
	Image(),
	clicked(false),
	function(nullptr),
	input(nullptr),
	state(forge::ButtonState::OUT_STATE),
	newState(forge::ButtonState::OUT_STATE),
	hoverTexture("default.png") {
	serializer(outTexture, "out");
	serializer(hoverTexture, "hover");
	serializer(clickedTexture, "clicked");
}

Button::~Button() {

}

bool Button::initComponent(ComponentData* data) {
	if (Image::initComponent(data)) {
		input = Input::GetInstance();
		setMaterial(outTexture);
		return true;
	}
	return false;
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
	if (state == forge::CLICKED_STATE && newState == forge::HOVER_STATE) {
		// callback

	}
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
