#include "Text.h"
#include "Serializer.h"
#include <imgui.h>
#include "GUIManager.h"
#include "RectTransform.h"

const std::string Text::id = "Text";

Text::Text() : UIComponent(),
    fontName(""),
    font(nullptr),
    color(forge::Vector4({ 1.0, 1.0, 1.0, 1.0 })),
    bgColor(forge::Vector4({ 0.0, 0.0, 0.0, 0.0 })) {
    serializer(fontName, "fontName");
    serializer(text, "text");
    serializer(color, "color");
    serializer(bgColor, "bgColor");
}

Text::~Text(){}

bool Text::initComponent(ComponentData* data) {
    if (UIComponent::initComponent(data)) {
        if (fontName != "") {
            changeFont(fontName);
        }

        if (size == forge::Vector2::ZERO) {
            ImVec2 textSize = ImGui::CalcTextSize(text);
            size = forge::Vector2(textSize.x * 1.07f, textSize.y);
        }

        return true;
    }
    return false;
}

void Text::update() {
    // Tamano y posicion de la ventana
    ImGui::SetNextWindowSize(gui->Vector2ToGUI(size));
    ImGui::SetNextWindowPos(gui->Vector2ToGUI(transform->getPosition()));

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    ImGui::PushStyleColor(ImGuiCol_WindowBg, gui->Vector4ToGUI(bgColor));
    ImGui::Begin(windowName, NULL, window_flags);

    // Texto con fuente cargada
    if(font != nullptr){
        ImGui::PushFont(font);
        ImGui::TextColored(gui->Vector4ToGUI(color), text);
        ImGui::PopFont();
    }
    else {
        ImGui::TextColored(gui->Vector4ToGUI(color), text);
        ImGui::SetWindowFontScale(1);
    }

    ImGui::PopStyleVar();
    ImGui::PopStyleColor();
    ImGui::End();
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

void Text::changeText(const char* text_) {
    text = text_;

    ImVec2 textSize = ImGui::CalcTextSize(text);
    size = forge::Vector2(textSize.x * 1.07f, textSize.y);
}

const char* Text::getText() {
    return text;
}