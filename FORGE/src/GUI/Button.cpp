#include "Button.h"
#include "Serializer.h"
#include <imgui.h>
#include "GUIManager.h"
#include "RectTransform.h"

const std::string Button::id = "Button";

Button::Button() : BaseButton(),
    fontName(""),
    font(nullptr) {
    serializer(text, "text");
    serializer(textColor, "textColor");
    serializer(buttonColor, "buttonColor");
    serializer(fontName, "fontName");
}

Button::~Button() { }

bool Button::initComponent(ComponentData* data) {
    if (BaseButton::initComponent(data)) {
        if (fontName != "") {
            changeFont(fontName);
        }

        if (size == forge::Vector2::ZERO) {
            ImVec2 textSize = ImGui::CalcTextSize(text);
            size = forge::Vector2(textSize.x * 1.1f, textSize.y * 1.3f);
        }

        return true;
    }
    return false;
}

void Button::update() {
    // Tamano y posicion de la ventana
    ImGui::SetNextWindowSize(gui->Vector2ToGUI(size));
    ImGui::SetNextWindowPos(gui->Vector2ToGUI(transform->getPosition()));

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    ImGui::Begin(windowName, NULL, window_flags);

    ImGui::PushStyleColor(ImGuiCol_Button, gui->Vector4ToGUI(buttonColor));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, gui->Vector4ToGUI(buttonHoverColor));
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, gui->Vector4ToGUI(buttonActiveColor));
    if (font != nullptr) {
        ImGui::PushFont(font);
        pressed = ImGui::Button(text, gui->Vector2ToGUI(size));
        ImGui::PopFont();
    }
    else {
        ImGui::Button(text);
    }

    if (pressed) {
        mainFunc = function;
    }

    ImGui::PopStyleVar();
    ImGui::PopStyleColor(3);
    ImGui::End();
}

void Button::setColor(forge::Vector4 color_) {
    buttonColor = color_;

    forge::Vector4 sumHover;
    forge::Vector4 sumActive;
    if (color_.getX() >= color_.getY() && color_.getX() >= color_.getZ()) {
        sumHover = forge::Vector4(0, 0.3f, 0.3f, 0);
        sumActive = forge::Vector4(0, 0.5f, 0.5f, 0);
    }
    else if (color_.getY() >= color_.getX() && color_.getY() >= color_.getZ()) {
        sumHover = forge::Vector4(0.3f, 0, 0.3f, 0);
        sumActive = forge::Vector4(0.5f, 0, 0.5f, 0);
    }
    else {
        sumHover = forge::Vector4(0.3f, 0.3f, 0, 0);
        sumActive = forge::Vector4(0.5f, 0.5f, 0, 0);
    }

    buttonHoverColor = color_ + sumHover;
    buttonActiveColor = color_ + sumActive;
}

void Button::setButtonColor(forge::Vector4 color_) {
    buttonColor = color_;
}

void Button::setButtonHoverColor(forge::Vector4 color_) {
    buttonHoverColor = color_;
}

void Button::setButtonActiveColor(forge::Vector4 color_) {
    buttonActiveColor = color_;
}

void Button::changeFont(std::string fontName_) {
    fontName = fontName_;
    if (fontName != "" && gui->getFonts().count(fontName)) {
        font = gui->getFonts()[fontName];
    }
}

void Button::changeButtonOpacity(float op) {
    buttonColor.setW(op);
    buttonHoverColor.setW(op);
    buttonActiveColor.setW(op);
}

void Button::changeText(const char* text_) {
    text = text_;
}