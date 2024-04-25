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
        /*if (fontName != "") {
            changeFont(fontName);
        }
        setBackground();*/

        gui->loadFont("Saeda.ttf");

        createOverlayContainer();

        ogreText = static_cast<Ogre::TextAreaOverlayElement*>(gui->getOverlayManager()->createOverlayElement("TextArea", elementID +  "textArea"));
        ogreText->setMetricsMode(Ogre::GMM_PIXELS);
        ogreText->setPosition(transform->getPosition().getX() / 2, transform->getPosition().getY() / 2);
        ogreText->setDimensions(1, 1);
        ogreText->setCaption(text);
        ogreText->setCharHeight(size.getY());
        ogreText->setFontName(fontName);
        // TODO: CONVERSOR DE VECTOR4 A COLORVALUE
        ogreText->setColour(Ogre::ColourValue(color.getX(), color.getY(), color.getZ(), color.getW()));
        ogreText->setAlignment(Ogre::TextAreaOverlayElement::Center);
        ogreContainer->addChild(ogreText);
        ogreText->show();

        registerElement(0);

        /*if (!Ogre::FontManager::getSingleton().resourceExists(font)) {
            if (eden_resources::ResourcesManager::Instance()->FileExist(font, eden_resources::ResourcesManager::Fonts)) {
                LoadFont(font);
            }
            else if (eden_resources::ResourcesManager::Instance()->FileExist("default.ttf", eden_resources::ResourcesManager::Default)) {
                font = "default.ttf";
                if (!Ogre::FontManager::getSingleton().resourceExists("default.ttf"))LoadFont("default.ttf");
            }
            else eden_error::ErrorHandler::Instance()->Exception("[SPY ERROR] Load Font Error:", "Failed to load the font: default.ttf");
        }*/

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
}

std::string Text::getText() const {
    return text;
}