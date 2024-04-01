#include "BaseButton.h"

const std::string BaseButton::id = "BaseButton";
std::function<void(void)> BaseButton::mainFunc = nullptr;

BaseButton::BaseButton(const char* bId, std::function<void(void)> funct, forge::Vector2 bSize, forge::Vector2 bPos)
    : UIComponent(bId, bPos), buttonId(bId), buttonSize(bSize), pressed(false), function(funct) {}

BaseButton::~BaseButton() { }

void BaseButton::setSize(forge::Vector2 size) {
    buttonSize = size;
}

bool BaseButton::isPressed() {
	return pressed;
}

void BaseButton::resetFunction() {
    mainFunc = nullptr;
}

bool BaseButton::mainFunctionCall() {
    if (mainFunc == nullptr) return false;
    mainFunc();
    return true;
}