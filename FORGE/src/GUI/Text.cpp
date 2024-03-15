#include "Text.h"
#include "GUI.h"

const std::string Text::id = "Text";

Text::Text(const char* textId, const char* text_, forge::Vector2 pos_, forge::Vector4 color_, std::string fontName_):
windowName(textId), text(text_), pos(pos_), color(color_), fontName(fontName_), font (nullptr), size(forge::Vector2::ZERO), bgColor(color_), gui(GUI::getInstance()){
    if (gui->getIds().count(textId)) {
    #ifdef _DEBUG
        std::cerr << "El id " + (std::string)textId + " ya existe\n";
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
    window_flags |= ImGuiWindowFlags_NoBackground;

    gui->getIds().insert(textId);
    if (fontName != "" && gui->getFonts().count(fontName)) {
        font = gui->getFonts()[fontName];
    }
    
}

void Text::update() {
    // Tamano y posicion de la ventana
    if (size == forge::Vector2::ZERO) {
        ImVec2 textSize = ImGui::CalcTextSize(text);
        ImGui::SetNextWindowSize(ImVec2(textSize.x * 1.07f, textSize.y));
    }
    else {
        ImGui::SetNextWindowSize(size);
    }
    ImGui::SetNextWindowPos(pos);
    ImGui::PushStyleColor(ImGuiCol_WindowBg, bgColor);
    ImGui::Begin(windowName, NULL, window_flags);
    // Texto con fuente cargada
    if(font != nullptr){
        ImGui::PushFont(font);
        ImGui::TextColored(color, text);
        ImGui::PopFont();
    }
    else {
        ImGui::TextColored(color, text);
        ImGui::SetWindowFontScale(1);
    }

    ImGui::End();
    ImGui::PopStyleColor();
}

void Text::setColor(forge::Vector4 color_) {
    color = color_;
}

void Text::setBackground(forge::Vector4 color_, forge::Vector2 size_) {
    window_flags -= ImGuiWindowFlags_NoBackground;
    bgColor = color_;
    if (size_ != forge::Vector2::ZERO) {
        size = size_;
    }
}

void Text::removeBackground() {
    window_flags += ImGuiWindowFlags_NoBackground;
}

void Text::changeFont(std::string fontName_) {
    fontName = fontName_;
    if (fontName != "" && gui->getFonts().count(fontName)) {
        font = gui->getFonts()[fontName];
    }
}

void Text::changeTextOpacity(float op) {
    color.setW(op);
}

void Text::changeBackgroundOpacity(float op) {
    bgColor.setW(op);
}