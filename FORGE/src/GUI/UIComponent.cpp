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

void UIComponent::createPanel() {
    overlayPanel = static_cast<Ogre::OverlayContainer*>(
        gui->getOverlayManager()->createOverlayElement("Panel", elementID));
    overlayPanel->setMetricsMode(Ogre::GMM_PIXELS);
}

void UIComponent::createOverlay(int depth) {
    overlay = gui->getOverlayManager()->create("over" + elementID);
    overlay->add2D(overlayPanel);
    setDepth(depth);

    overlay->show();
}

void UIComponent::destroyPanel() {
    gui->getOverlayManager()->destroyOverlayElement(overlayPanel);
    overlayPanel = nullptr;
}

void UIComponent::destroyOverlay() {
    gui->getOverlayManager()->destroy("over" + elementID);
    overlay = nullptr;
}

UIComponent::UIComponent() :
    gui(nullptr),
    transform(nullptr),
    zOrder(0),
    overlayPanel(nullptr),
    overlay(nullptr),
    elementID("") {
    serializer(zOrder, "depth");
}

UIComponent::~UIComponent() {
    gui->deleteCanvasElement(this);
}

bool UIComponent::initComponent(ComponentData* data) {
    if (entity->hasComponent("RectTransform")) {
        transform = entity->getComponent<RectTransform>();
        gui = GUIManager::GetInstance();

        elementID = gui->getRandomName();
        while (gui->getIds().count(elementID) != 0) {
            elementID = gui->getRandomName();
        }
        gui->getIds().insert(elementID);
        gui->addCanvasElement(this);
        return true;
    }
    else {
        std::cerr << "ERROR: Se requiere un componente RectTransform para generar un UIComponent\n";
    }
    return false;
}

void UIComponent::update() {

}

void UIComponent::onEnabled() {
    gui->addCanvasElement(this);
}

void UIComponent::onDisabled() {
    gui->deleteCanvasElement(this);
}

void UIComponent::resize(forge::Vector2  const& prev, forge::Vector2 const& updated) {
    forge::Vector2 scale = transform->getScale();
    forge::Vector2 position = transform->getPosition();

    float factorX = updated.getX() / prev.getX();
    float factorY = updated.getY() / prev.getY();

    transform->setScale(forge::Vector2(static_cast<int>(scale.getX() * factorY),
        static_cast<int>(scale.getY() * factorY)));
    transform->setPosition(forge::Vector2(static_cast<int>(position.getX() * factorX),
        static_cast<int>(position.getY() * factorY)));

    overlayPanel->setDimensions(transform->getScale().getX(), transform->getScale().getY());
    overlayPanel->setPosition(transform->getPosition().getX(), transform->getPosition().getY());
}

forge::Vector2 UIComponent::getPosition() const {
    return transform->getPosition();
}

void UIComponent::setPosition(forge::Vector2 const& p) {
    transform->setPosition(p);
    overlayPanel->setPosition(transform->getPosition().getX(), transform->getPosition().getY());
}

void UIComponent::setDepth(int zO) {
    overlay->setZOrder(Ogre::ushort(zO));
}
