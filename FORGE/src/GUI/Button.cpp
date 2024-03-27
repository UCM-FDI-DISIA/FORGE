#include "Button.h"
#include "GUI.h"

const std::string Button::id = "Button";

Button::Button(const char* buttonId, const char* buttonText, forge::Vector2 pos_) : UIComponent(buttonId, pos_),
    text(buttonText), textColor(forge::Vector4({ 1.0, 1.0, 1.0, 1.0 })), fontName(""), font(nullptr),
    buttonSize(forge::Vector2::ZERO),  buttonColor(forge::Vector4({ 1.0, 1.0, 1.0, 1.0 })), pressed(false) { }

Button::~Button() { }

bool Button::update() {
    // Tamano y posicion de la ventana
    if (buttonSize == forge::Vector2::ZERO) {
        ImVec2 textSize = ImGui::CalcTextSize(text);
        buttonSize = forge::Vector2(textSize.x * 1.1f, textSize.y * 1.3f);
    }
    ImGui::SetNextWindowSize(buttonSize);
    ImGui::SetNextWindowPos(pos);

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    ImGui::Begin(windowName, NULL, window_flags);

    ImGui::PushStyleColor(ImGuiCol_Button, buttonColor);
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, buttonHoverColor);
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, buttonActiveColor);
    if (font != nullptr) {
        ImGui::PushFont(font);
        pressed = ImGui::Button(text, buttonSize);
        ImGui::PopFont();
    }
    else {
        ImGui::Button(text);
    }

    ImGui::PopStyleVar();
    ImGui::PopStyleColor(3);
    ImGui::End();
    return true;
}

void Button::setSize(forge::Vector2 size) {
    buttonSize = size;
}

void Button::setColor(forge::Vector4 color_) {
    buttonColor = color_;

    forge::Vector4 sumHover;
    forge::Vector4 sumActive;
    if (color_.getX() >= color_.getY() && color_.getX() >= color_.getZ()) {
        sumHover = forge::Vector4(0, 0.3, 0.3, 0);
        sumActive = forge::Vector4(0, 0.5, 0.5, 0);
    }
    else if (color_.getY() >= color_.getX() && color_.getY() >= color_.getZ()) {
        sumHover = forge::Vector4(0.3, 0, 0.3, 0);
        sumActive = forge::Vector4(0.5, 0, 0.5, 0);
    }
    else {
        sumHover = forge::Vector4(0.3, 0.3, 0, 0);
        sumActive = forge::Vector4(0.5, 0.5, 0, 0);
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

bool Button::isPressed() {
    return pressed;
}