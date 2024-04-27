#include "Text.h"
#pragma warning(push)
#pragma warning(disable : 26495)
#pragma warning(disable : 4251)
#include <OgreFont.h>
#include <OgreFontManager.h>
#include <OgreOverlayManager.h>
#include <OgreTextAreaOverlayElement.h>
#include <OgreOverlayContainer.h>
#include <OgreOverlay.h>
#pragma warning(pop)
#include "Serializer.h"
#include "GUIManager.h"
#include "RectTransform.h"

const std::string Text::id = "Text";

Text::Text() : UIComponent(),
    textAreaOverlay(nullptr),
    fontName(""),
    color(forge::Vector4({ 1.0, 1.0, 1.0, 1.0 })),
    bgColor(forge::Vector4({ 0.0, 0.0, 0.0, 1.0 })) {
    serializer(fontName, "fontName");
    serializer(text, "text");
    serializer(color, "color");
    serializer(bgColor, "bgColor");
}

Text::~Text() {
    destroyText();
}

bool Text::initComponent(ComponentData* data) {
    if (UIComponent::initComponent(data)) {
        createText();
        return true;
    }
    return false;
}

void Text::onEnabled() {
    createText();
}

void Text::onDisabled() {
    destroyText();
}

void Text::createText() {
    createPanel();

    textAreaOverlay = static_cast<Ogre::TextAreaOverlayElement*>(gui->getOverlayManager()->createOverlayElement("TextArea", elementID + "textArea"));
    textAreaOverlay->setMetricsMode(Ogre::GMM_PIXELS);
    forge::Vector2 center = getCenterPoint();
    textAreaOverlay->setPosition(center.getX(), center.getY());
    textAreaOverlay->setDimensions(size.getX() * transform->getScale().getX(), size.getY() * transform->getScale().getY());
    textAreaOverlay->setCaption(text);
    textAreaOverlay->setCharHeight(size.getY() * transform->getScale().getY());
    setFont(fontName);
    setColor(color);
    textAreaOverlay->setAlignment(Ogre::TextAreaOverlayElement::Center);
    overlayPanel->addChild(textAreaOverlay);

    createOverlay(zOrder);
}

void Text::destroyText() {
    gui->getOverlayManager()->destroyOverlayElement(textAreaOverlay);
    destroyPanel();
    destroyOverlay();
    textAreaOverlay = nullptr;
}

//void Text::setBackground(forge::Vector4 color_, forge::Vector2 size_) {
//    bgColor = color_;
//    /*if (size_ != forge::Vector2::ZERO) {
//        size = size_;
//    }*/
//}

//void Text::removeBackground() {
//    
//}


void Text::changeBackgroundOpacity(float op) {
    bgColor.setW(op);
}

std::string Text::getText() const {
    return text;
}

forge::Vector4 Text::getColor() const {
    return color;
}

void Text::setSize(forge::Vector2 const& s) {
    UIComponent::setSize(s);
    textAreaOverlay->setDimensions(size.getX() * transform->getScale().getX(), size.getY() * transform->getScale().getY());
}

void Text::setFont(std::string const& fontName_) {
    if (fontName_ != "" && !gui->hasFont(fontName_)) {
        fontName = fontName_;
        gui->loadFont(fontName);
        textAreaOverlay->setFontName(fontName);
    }
    else {
        textAreaOverlay->setFontName("Saeda.ttf");
    }
}

void Text::setText(std::string const& text_) {
    text = text_;
    textAreaOverlay->setCaption(text);
}

void Text::setColor(forge::Vector4 color_) {
    color = color_;
    textAreaOverlay->setColour(gui->Vector4ToColorValue(color));
}

void Text::setTextOpacity(float op) {
    color.setW(op);
    textAreaOverlay->setColour(gui->Vector4ToColorValue(color));
}

void Text::setTextAligment(forge::Alignment a) {
    switch (a) {
        case forge::CENTER:
            textAreaOverlay->setAlignment(Ogre::TextAreaOverlayElement::Alignment::Center);
            break;
        case forge::RIGHT:
            textAreaOverlay->setAlignment(Ogre::TextAreaOverlayElement::Alignment::Right);
            break;
        case forge::LEFT:
            textAreaOverlay->setAlignment(Ogre::TextAreaOverlayElement::Alignment::Left);
            break;
    }
}