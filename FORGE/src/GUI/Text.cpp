#include "Text.h"
#include "GUI.h"

const std::string Text::id = "Text";

Text::Text(const char* textId, const char* text_, forge::Vector2 pos_) : UIComponent(textId, pos_), text(text_), color(forge::Vector4({ 1.0, 1.0, 1.0, 1.0 })), 
fontName(""), font(nullptr), size(forge::Vector2::ZERO), bgColor(forge::Vector4({ 1.0, 1.0, 1.0, 1.0 })) { }

Text::~Text(){}

bool Text::update() {
    // Tamano y posicion de la ventana
    if (size == forge::Vector2::ZERO) {
        ImVec2 textSize = ImGui::CalcTextSize(text);
        ImGui::SetNextWindowSize(ImVec2(textSize.x * 1.07f, textSize.y));
    }
    else {
        ImGui::SetNextWindowSize(size);
    }
    ImGui::SetNextWindowPos(pos);

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
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

    ImGui::PopStyleVar();
    ImGui::PopStyleColor();
    ImGui::End();
    return true;
}

void Text::setColor(forge::Vector4 color_) {
    color = color_;
}
void Text::setSize(forge::Vector2 size_) {
    size = size_;
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

void Text::changeText(const char* text_) {
    text = text_;
}

const char* Text::getText() {
    return text;
}