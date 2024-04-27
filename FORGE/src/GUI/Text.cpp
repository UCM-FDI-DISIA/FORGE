#include "Text.h"
#pragma warning(push)
#pragma warning(disable : 26495)
#pragma warning(disable : 4251)
#include <OgreSharedPtr.h>
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
    fontHeight(50),
    color(forge::Vector4({ 1.0, 1.0, 1.0, 1.0 })),
    bgColor(forge::Vector4({ 0.0, 0.0, 0.0, 1.0 })) {
    serializer(fontName, "fontName");
    serializer(fontHeight, "fontHeight");
    serializer(text, "text");
    serializer(color, "color");
    serializer(bgColor, "bgColor");
}

Text::~Text() {
    if (textAreaOverlay != nullptr) destroyText();
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
    setText(text);
    setHeight(fontHeight);
    setFont(fontName);
    setColor(color);
    setTextAligment(forge::Alignment::CENTER);
    setPosition(getUpperLeftPoint());
    overlayPanel->addChild(textAreaOverlay);
    createOverlay(zOrder);
}

void Text::destroyText() {
    gui->getOverlayManager()->destroyOverlayElement(textAreaOverlay);
    destroyPanel();
    destroyOverlay();
    textAreaOverlay = nullptr;
}

float Text::calculateTextWidth() {
    float w = 0;
    Ogre::FontPtr font = gui->getFontManager()->getByName(fontName, "General");
    for (char& l : text) {
        w += (font.get()->getGlyphAspectRatio(l) * fontHeight);
    }
    return w;
}

forge::Vector2 Text::getUpperLeftPoint() {
    Ogre::FontPtr font = gui->getFontManager()->getByName("Saeda.ttf", "General");
    forge::Vector2 point = 
        forge::Vector2(transform->getPosition().getX() + (calculateTextWidth() / 2)
            , transform->getPosition().getY());
    return point;
}

void Text::changeBackgroundOpacity(float op) {
    bgColor.setW(op);
}

std::string Text::getText() const {
    return text;
}

forge::Vector4 Text::getColor() const {
    return color;
}

void Text::setPosition(forge::Vector2 const& newPosition) {
    transform->setPosition(newPosition);
    textAreaOverlay->setPosition(newPosition.getX(), newPosition.getY());
}

void Text::setHeight(int fHeight) {
    fontHeight = fHeight;
    textAreaOverlay->setCharHeight(fHeight);
}

void Text::setFont(std::string const& fontName_) {
    if (fontName_ != "" && !gui->hasFont(fontName_)) {
        fontName = fontName_;
        gui->loadFont(fontName);
        textAreaOverlay->setFontName(fontName);
    }
    else {
        textAreaOverlay->setFontName("Saeda.ttf");
        fontName = "Saeda.ttf";
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