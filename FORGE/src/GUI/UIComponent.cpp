#include "UIComponent.h"
#include "GUI.h"

UIComponent::UIComponent(const char* id, forge::Vector2 pos_) : windowName(id), pos(pos_), gui(GUI::getInstance()) {
    if (gui->getIds().count(id)) {
        #ifdef _DEBUG
                std::cerr << "El id " + (std::string)id + " ya existe\n";
        #endif // _DEBUG
        return;
    }

    // Flags
    window_flags |= ImGuiWindowFlags_NoTitleBar;
    window_flags |= ImGuiWindowFlags_NoScrollbar;
    window_flags |= ImGuiWindowFlags_NoMove;
    window_flags |= ImGuiWindowFlags_NoResize;
    window_flags |= ImGuiWindowFlags_NoCollapse;
    window_flags |= ImGuiWindowFlags_NoNav;
    //window_flags |= ImGuiWindowFlags_NoBackground;

    gui->getIds().insert(id);
}
UIComponent::~UIComponent() {

}

void UIComponent::setPosition(forge::Vector2 pos_) {
    pos = pos_;
}