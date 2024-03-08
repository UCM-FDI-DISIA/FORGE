#include "GUI.h"

std::unique_ptr<GUI> GUI::instance = nullptr;

GUI::GUI(){}
GUI::~GUI(){}

GUI* GUI::getInstance() {
    if (instance.get() != nullptr) return instance.get();
    return (instance = std::unique_ptr<GUI>(new GUI())).get();
}
void GUI::createText(const char * text/*, forge::Vector2 pos*/, float fontSize, Vector4 color) {
    ImGuiWindowFlags window_flags = 0;
    window_flags |= ImGuiWindowFlags_NoTitleBar;
    window_flags |= ImGuiWindowFlags_NoScrollbar;
    window_flags |= ImGuiWindowFlags_NoMove;
    window_flags |= ImGuiWindowFlags_NoResize;
    window_flags |= ImGuiWindowFlags_NoCollapse;
    window_flags |= ImGuiWindowFlags_NoNav;
    window_flags |= ImGuiWindowFlags_NoBackground;

    //ImGui::SetNextWindowPos(ImVec2(pos.getX(), pos.getY()), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_FirstUseEver);
    // Tamano de la ventana
    ImGui::SetNextWindowSize(ImVec2(0, 0), ImGuiCond_FirstUseEver);
    ImGui::Begin("akfbsdk", NULL, window_flags);
    ImGui::TextColored(ImVec4(color.x, color.y, color.z, color.w), text);
    //ImGui::Text(text);
    ImGui::SetWindowFontScale(fontSize);
    ImGui::End();
}