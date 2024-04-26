#include "Text.h"
#include <OgreFont.h>
#include <OgreFontManager.h>
#include <OgreOverlayManager.h>
#include <OgreTextAreaOverlayElement.h>
#include <OgreOverlayContainer.h>
#include <OgreOverlay.h>
#include "Serializer.h"
#include "GUIManager.h"
#include "RectTransform.h"

const std::string Text::id = "Text";

Text::Text() : UIComponent(),
    textAreaOverlay(nullptr),
    fontName(""),
    font(nullptr),
    color(forge::Vector4({ 1.0, 1.0, 1.0, 1.0 })),
    bgColor(forge::Vector4({ 0.0, 0.0, 0.0, 1.0 })) {
    serializer(fontName, "fontName");
    serializer(text, "text");
    serializer(color, "color");
    serializer(bgColor, "bgColor");
}

Text::~Text() {}

bool Text::initComponent(ComponentData* data) {
    if (UIComponent::initComponent(data)) {
        if (fontName != "") {
            gui->loadFont("Saeda.ttf");
        }

        createPanel();

        textAreaOverlay = static_cast<Ogre::TextAreaOverlayElement*>(gui->getOverlayManager()->createOverlayElement("TextArea", elementID +  "textArea"));
        textAreaOverlay->setMetricsMode(Ogre::GMM_PIXELS);
        textAreaOverlay->setPosition(transform->getPosition().getX() / 2, transform->getPosition().getY() / 2);
        textAreaOverlay->setDimensions(size.getX(), size.getY());
        textAreaOverlay->setCaption(text);
        textAreaOverlay->setCharHeight(size.getY());
        textAreaOverlay->setFontName(fontName);
        textAreaOverlay->setColour(gui->Vector4ToColorValue(color));
        textAreaOverlay->setAlignment(Ogre::TextAreaOverlayElement::Center);
        overlayPanel->addChild(textAreaOverlay);

        createOverlay(1);

        return true;
    }
    return false;
}

void Text::onEnabled() {

}

void Text::onDisabled() {

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
    textAreaOverlay->setCaption(text);
}

std::string Text::getText() const {
    return text;
}