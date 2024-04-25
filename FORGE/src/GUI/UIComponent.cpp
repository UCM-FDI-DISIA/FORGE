#include "UIComponent.h"
#include <OgreOverlayContainer.h>
#include <OgreOverlayManager.h>
#include <OgreOverlay.h>
#include "Entity.h"
#include "Serializer.h"
#include "GUIManager.h"
#include "RectTransform.h"

const std::string UIComponent::id = "UIComponent";

void UIComponent::createOverlayContainer() {
    ogreContainer = static_cast<Ogre::OverlayContainer*>(
        gui->getOverlayManager()->createOverlayElement("Panel", elementID));
    ogreContainer->setMetricsMode(Ogre::GMM_RELATIVE);
    ogreContainer->setPosition(transform->getPosition().getX(), transform->getPosition().getY());
    ogreContainer->setDimensions(size.getX(), size.getY());
    ogreContainer->show();
}

void UIComponent::registerElement(int depth) {
    ogreElement = gui->getOverlayManager()->create("over" + elementID);
    ogreElement->add2D(ogreContainer);
    ogreElement->show();
    setDepth(depth);
}

UIComponent::UIComponent() :
    gui(GUIManager::GetInstance()),
    transform(nullptr),
    size(forge::Vector2::ZERO),
    depth(0) {
    serializer(elementID, "id");
    serializer(depth, "depth");
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
	return size;
}

void UIComponent::setSize(forge::Vector2 const& s) {
	size = s;
}

void UIComponent::setDepth(int depth) {
    ogreElement->setZOrder(Ogre::ushort(depth));
}
