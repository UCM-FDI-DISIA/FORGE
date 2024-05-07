#include "UIComponent.h"
#pragma warning(push)
#pragma warning(disable : 26439)
#pragma warning(disable : 26451)
#pragma warning(disable : 26495)
#pragma warning(disable : 4251)
#include <OgreOverlayContainer.h>
#include <OgreOverlayManager.h>
#include <OgreOverlay.h>
#pragma warning(pop)
#include "Entity.h"
#include "Serializer.h"
#include "GUIManager.h"
#include "RectTransform.h"

const std::string UIComponent::id = "UIComponent";

Ogre::OverlayContainer* UIComponent::createPanel() {
    Ogre::OverlayContainer* panel = static_cast<Ogre::OverlayContainer*>(
        gui.getOverlayManager()->createOverlayElement("Panel", elementID));
    panel->setMetricsMode(Ogre::GMM_PIXELS);
    return panel;
}

Ogre::Overlay* UIComponent::createOverlay(Ogre::OverlayContainer* panel, int depth) {
    Ogre::Overlay* over = gui.getOverlayManager()->create("over" + elementID);
    over->add2D(panel);
    over->setZOrder(Ogre::ushort(depth));

    over->show();
    return over;
}

void UIComponent::destroyPanel(Ogre::OverlayContainer* _panel) {
    gui.getOverlayManager()->destroyOverlayElement(_panel);
}

void UIComponent::destroyOverlay(Ogre::Overlay* _over) {
    gui.getOverlayManager()->destroy(_over);
}

UIComponent::UIComponent() :
    gui(*GUIManager::GetInstance()),
    transform(nullptr),
    zOrder(0),
    overlayPanel(nullptr),
    overlay(nullptr),
    elementID("") {
    serializer(zOrder, "depth");
}

UIComponent::~UIComponent() {
    gui.deleteCanvasElement(this);
    overlay = nullptr;
    overlayPanel = nullptr;
}

bool UIComponent::initComponent(ComponentData* data) {
    if (!entity->hasComponent(RectTransform::id)) {
        throwError(false, "Se requiere un componente RectTransform para generar un UIComponent");
    }
    transform = entity->getComponent<RectTransform>();

    elementID = gui.getRandomName();
    while (gui.getIds().count(elementID) != 0) {
        elementID = gui.getRandomName();
    }
    gui.getIds().insert(elementID);
    gui.addCanvasElement(this);
    return true;
}

void UIComponent::onEnabled() {
    gui.addCanvasElement(this);
}

void UIComponent::onDisabled() {
    gui.deleteCanvasElement(this);
}

void UIComponent::resize(forge::Vector2 const& prev, forge::Vector2 const& updated) {
    forge::Vector2 scale = transform->getScale();
    forge::Vector2 position = transform->getPosition();

    float factorX = updated.getX() / prev.getX();
    float factorY = updated.getY() / prev.getY();

    transform->setScale(forge::Vector2(scale.getX() * factorY, scale.getY() * factorY));
    transform->setPosition(forge::Vector2(position.getX() * factorX, position.getY() * factorY));

    overlayPanel->setDimensions(transform->getScale().getX(), transform->getScale().getY());
    overlayPanel->setPosition(transform->getPosition().getX(), transform->getPosition().getY());
}

forge::Vector2 const& UIComponent::getPosition() const {
    return transform->getPosition();
}

void UIComponent::setPosition(forge::Vector2 const& newPosition) {
    transform->setPosition(newPosition);
    overlayPanel->setPosition(transform->getPosition().getX(), transform->getPosition().getY());
}

void UIComponent::setDepth(int _zOrder) {
    zOrder = _zOrder;
    overlay->setZOrder(Ogre::ushort(_zOrder));
}
