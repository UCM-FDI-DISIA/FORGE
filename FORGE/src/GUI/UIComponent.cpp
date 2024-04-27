#include "UIComponent.h"
#include <OgreOverlayContainer.h>
#include <OgreOverlayManager.h>
#include <OgreOverlay.h>
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
        return true;
    }
    else {
        std::cerr << "ERROR: Se requiere un componente RectTransform para generar un UIComponent\n";
    }
    return false;
}

//forge::Vector2 UIComponent::getSize() const {
//	return size;
//}

void UIComponent::setPosition(forge::Vector2 const& p) {
    transform->setPosition(p);
    overlayPanel->setPosition(transform->getPosition().getX(), transform->getPosition().getY());
}

//void UIComponent::setSize(forge::Vector2 const& s) {
//	size = s;
//    overlayPanel->setDimensions(size.getX() * transform->getScale().getX(), size.getY() * transform->getScale().getY());
//}

void UIComponent::setDepth(int zO) {
    overlay->setZOrder(Ogre::ushort(zO));
}
