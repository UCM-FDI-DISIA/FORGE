#include "Text.h"
#include <OgreFont.h>
#include "Serializer.h"

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

Text::~Text() {}

bool Text::initComponent(ComponentData* data) {
    if (UIComponent::initComponent(data)) {
        if (fontName != "") {
            changeFont(fontName);
        }
        setBackground();

        return true;
    }
    return false;
}

void Text::setColor(forge::Vector4 color_) {
    color = color_;
}

void Text::setBackground(forge::Vector4 color_, forge::Vector2 size_) {
    bgColor = color_;
    if (size_ != forge::Vector2::ZERO) {
        size = size_;
    }
}

void Text::removeBackground() {
    
}

void Text::changeFont(std::string const& fontName_) {
    fontName = fontName_;
}

void Text::changeTextOpacity(float op) {
    color.setW(op);
}

void Text::changeBackgroundOpacity(float op) {
    bgColor.setW(op);
}

void Text::changeText(std::string const& text_) {
    text = text_;
}

std::string Text::getText() const {
    return text;
}