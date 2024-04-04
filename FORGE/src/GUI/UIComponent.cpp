#include "UIComponent.h"
#include "Entity.h"
#include "Serializer.h"

const std::string UIComponent::id = "UIComponent";

UIComponent::UIComponent() :
    gui(nullptr),
    window_flags(0),
    transform(nullptr),
    size(forge::Vector2::ZERO) {
    serializer(windowName, "id");
}

UIComponent::~UIComponent() {

}

bool UIComponent::initComponent(ComponentData* data) {
    if (entity->hasComponent("RectTransform")) {
        transform = entity->getComponent<RectTransform>();

        gui = GUIManager::getInstance();
        if (gui->getIds().count(windowName) == 0) {
            gui->getIds().insert(windowName);

            window_flags |= ImGuiWindowFlags_NoTitleBar;
            window_flags |= ImGuiWindowFlags_NoScrollbar;
            window_flags |= ImGuiWindowFlags_NoMove;
            window_flags |= ImGuiWindowFlags_NoResize;
            window_flags |= ImGuiWindowFlags_NoCollapse;
            window_flags |= ImGuiWindowFlags_NoNav;
            window_flags |= ImGuiWindowFlags_NoBackground;

            return true;
        }
        else {
            std::cerr << "El id " + (std::string)windowName + " ya existe\n";
        }
    }
    else {
        std::cerr << "ERROR: Se requiere un componente RectTransform para generar un UIComponent\n";
    }

    return false;
}

forge::Vector2 UIComponent::getSize() {
    return size;
}