#include "Button.h"
#include "Serializer.h"
#include "Entity.h"
#include "GUIManager.h"
#include "Input.h"
#include "RectTransform.h"
#include "Image.h"

const std::string Button::id = "Button";
std::function<void(void)> Button::mainFunc = nullptr;

void Button::changeButtonImage() {
	if (state == forge::IDLE && image->getTexture() != idleTexture) {
		image->setMaterial(idleTexture);
	}
	else if (state == forge::HOVER && image->getTexture() != hoverTexture) {
		image->setMaterial(hoverTexture);
	}
}

Button::Button() :
	pressed(false),
	function(nullptr),
	image(nullptr),
	input(nullptr),
	state(forge::ButtonState::IDLE),
	hoverTexture("default.png") {
	serializer(hoverTexture, "hover");
	// Ver como cargar una funcion desde Lua
}

Button::~Button() {

}

bool Button::initComponent(ComponentData* data) {
	if (UIComponent::initComponent(data)) {
		if (entity->hasComponent("Image")) {
			input = Input::GetInstance();
			image = entity->getComponent<Image>();
			idleTexture = image->getTexture();
			return true;
		}
		else {
			std::cerr << "ERROR: Una entidad con componente Button debe contar con un componente Image tambien";
		}
	}
	return false;
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
	return pressed;
}
