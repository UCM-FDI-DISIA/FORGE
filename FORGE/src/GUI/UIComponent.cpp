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
    overlayPanel->setPosition(transform->getPosition().getX(), transform->getPosition().getY());
    overlayPanel->setDimensions(transform->getScale().getX(), transform->getScale().getY());
}

void UIComponent::createOverlay(int depth) {
    overlay = gui->getOverlayManager()->create("over" + elementID);
    overlay->add2D(overlayPanel);
    setDepth(depth);

    overlay->show();
}

UIComponent::UIComponent() :
    gui(GUIManager::GetInstance()),
    transform(nullptr),
    zOrder(0),
    overlayPanel(nullptr),
    overlay(nullptr) {
    serializer(elementID, "id");
    serializer(zOrder, "depth");
}

UIComponent::~UIComponent() {

}

bool UIComponent::initComponent(ComponentData* data) {
    if (entity->hasComponent("RectTransform")) {
        transform = entity->getComponent<RectTransform>();
        gui = GUIManager::GetInstance();
        if (gui->getIds().count(elementID) == 0) {
            gui->getIds().insert(elementID);
            return true;
        }
        else {
            std::cerr << "ERROR: El id " + (std::string)elementID + " ya existe\n";
        }
    }
    else {
        std::cerr << "ERROR: Se requiere un componente RectTransform para generar un UIComponent\n";
    }

    return false;
}

void UIComponent::onEnabled() {

}

void UIComponent::onDisabled() {
	
}

forge::Vector2 UIComponent::getSize() const {
	return transform->getScale();
}

void UIComponent::setSize(forge::Vector2 const& s) {
	transform->setScale(s);
}

void UIComponent::setDepth(int zO) {
    overlay->setZOrder(Ogre::ushort(zO));
}
