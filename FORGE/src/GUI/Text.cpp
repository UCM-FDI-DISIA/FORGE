#include "Text.h"
#pragma warning(push)
#pragma warning(disable : 26439)
#pragma warning(disable : 26451)
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

Text::Text() :
    textAreaOverlay(nullptr),
    fontName(""),
    fontHeight(50),
    color(1.0f, 1.0f, 1.0f, 1.0f),
    bgColor(0.0f, 0.0f, 0.0f, 1.0f),
    fixedPosition() {
    serializer(fontName, "fontName");
    serializer(fontHeight, "fontHeight");
    serializer(text, "text");
    serializer(color, "color");
    serializer(bgColor, "bgColor");
}

Text::~Text() {
    if (textAreaOverlay != nullptr) {
        destroyText();
    }
}

bool Text::initComponent(ComponentData* data) {
    if (UIComponent::initComponent(data)) {
        fontHeight = static_cast<int>(transform->getScale().getY() * fontHeight);
        createText();
        return true;
    }
    throwError(false, "No se pudo crear el componente Text");
}

void Text::onEnabled() {
    UIComponent::onEnabled();
    createText();
}

void Text::onDisabled() {
    UIComponent::onDisabled();
    destroyText();
}

void Text::resize(forge::Vector2 const& prev, forge::Vector2 const& updated) {
    UIComponent::resize(prev, updated);

    float factorY = updated.getY() / prev.getY();
    fontHeight = static_cast<int>(factorY * fontHeight);
    overlayPanel->setPosition(0.0f, 0.0f);
    setPosition(transform->getPosition());
    setHeight(fontHeight);
}

void Text::createText() {
    // Se crea el panel
    overlayPanel = createPanel();
    // Se crea el texto y se le setean los parametros: fuente, texto, altura de la letra, color, alineacion y posicion
    textAreaOverlay = static_cast<Ogre::TextAreaOverlayElement*>(gui.getOverlayManager()->createOverlayElement("TextArea", elementID + "textArea"));
    textAreaOverlay->setMetricsMode(Ogre::GMM_PIXELS);
    setFont(fontName);
    setText(text);
    setHeight(fontHeight);
    setColor(color);
    setTextAligment(forge::Alignment::CENTER);
    setPosition(transform->getPosition());
    // Se adjunta al panel y se crea el Overlay
    overlayPanel->addChild(textAreaOverlay);
    overlay = createOverlay(overlayPanel, zOrder);
}

void Text::destroyText() {
    // Destruye de menor a mayor (texto < panel < Overlay)
    gui.getOverlayManager()->destroyOverlayElement(textAreaOverlay);
    destroyPanel(overlayPanel);
    destroyOverlay(overlay);
    textAreaOverlay = nullptr;
}

float Text::calculateTextWidth() {
    float w = 0;
    Ogre::FontPtr font = gui.getFontManager()->getByName(fontName, "General");
    // Sumamos la anchura de cada caracter del texto 
    // ...getGlynphAspectRatio -> devuelve la relacion entre anchura y altura de una letra
    for (char& l : text) {
        w += (font.get()->getGlyphAspectRatio(l) * fontHeight);
    }
    return w;
}

void Text::fixPosition() {
    fixedPosition = 
        forge::Vector2(transform->getPosition().getX() + (calculateTextWidth() / 2.0f), transform->getPosition().getY());
    textAreaOverlay->setPosition(fixedPosition.getX(), fixedPosition.getY());
}

void Text::changeBackgroundOpacity(float op) {
    bgColor.setW(op);
}

std::string const& Text::getText() const {
    return text;
}

forge::Vector4 const& Text::getColor() const {
    return color;
}

void Text::setPosition(forge::Vector2 const& newPosition) {
    transform->setPosition(newPosition);
    fixPosition();
}

void Text::setHeight(int fHeight) {
    fontHeight = fHeight;
    textAreaOverlay->setCharHeight(Ogre::Real(fHeight));
}

void Text::setFont(std::string const& fontName_) {
    // Si se ha especificado una fuente...
    if (fontName_ != "") {
        // Si no estaba cargada...
        if (!gui.hasFont(fontName_)) {
            gui.loadFont(fontName);
        }
        fontName = fontName_;
    }
    // Si no se le ha especificado una fuente
    else {
        fontName = "Saeda.ttf";
    }
    textAreaOverlay->setFontName(fontName);
}

void Text::setText(std::string const& text_) {
    text = text_;
    textAreaOverlay->setCaption(text);
}

void Text::setColor(forge::Vector4 const& color_) {
    color = color_;
    textAreaOverlay->setColour(gui.Vector4ToColorValue(color));
}

void Text::setTextOpacity(float op) {
    color.setW(op);
    textAreaOverlay->setColour(gui.Vector4ToColorValue(color));
}

void Text::setTextAligment(forge::Alignment alignment) {
    switch (alignment) {
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