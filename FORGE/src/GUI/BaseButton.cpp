#include "BaseButton.h"
#include "Serializer.h"

const std::string BaseButton::id = "BaseButton";
std::function<void(void)> BaseButton::mainFunc = nullptr;

BaseButton::BaseButton() : UIComponent(),
    pressed(false) {
    serializer(buttonId, "buttonId");
    serializer(function, "function");
}

BaseButton::~BaseButton() { }

bool BaseButton::initComponent(ComponentData* data) {
    if (UIComponent::initComponent(data)) {
        return true;
    }
    return false;
}

void BaseButton::resetFunction() {
    mainFunc = nullptr;
}

bool BaseButton::mainFunctionCall() {
    if (mainFunc == nullptr) return false;
    mainFunc();
    return true;
}

bool BaseButton::isPressed() {
    return pressed;
}