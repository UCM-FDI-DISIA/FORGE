#include "UIComponent.h"
#include <OgreOverlayContainer.h>
#include "Entity.h"
#include "Serializer.h"
#include "GUIManager.h"
#include "RectTransform.h"

const std::string UIComponent::id = "UIComponent";

void UIComponent::createOverlayContainer() {
    /* ogreContainer = static_cast<Ogre::OverlayContainer*>(gui->getOverlayManager()->createOverlayElement("Panel", id + std::to_string(_numUIElements)));
    ogreContainer->setMetricsMode(Ogre::GMM_PIXELS);
    ogreContainer->setPosition(xPos, yPos);
    ogreContainer->setDimensions(width, height);
    ogreContainer->show();*/
}

void UIComponent::registerElement() {

}

UIComponent::UIComponent() :
    gui(GUIManager::GetInstance()),
    transform(nullptr),
    size(forge::Vector2::ZERO) {

}

UIComponent::~UIComponent() {

}

bool UIComponent::initComponent(ComponentData* data) {
    if (entity->hasComponent("RectTransform")) {
        transform = entity->getComponent<RectTransform>();
        gui = GUIManager::GetInstance();
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

FORGE_API forge::Vector2 UIComponent::getSize() const {
	return size;
}

FORGE_API void UIComponent::setSize(forge::Vector2 const& s) {
	size = s;
}