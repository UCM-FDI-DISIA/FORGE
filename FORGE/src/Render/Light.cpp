#include "Light.h"
#include "RenderManager.h"
#include "Entity.h"
#include "Serializer.h"
#include "OgreLight.h"

const std::string Light::id = "Light";

Light::Light() :
    ogreLight(nullptr),
    renderManager(nullptr) {
    serializer(type, "type");
}

Light::~Light() {
    if(ogreLight != nullptr && renderManager != nullptr)
    {
        renderManager->removeNode(ogreLight);
    }
}

bool Light::initComponent(ComponentData* data) {
    if(entity->hasComponent("Transform")) {
        renderManager = RenderManager::getInstance();
        ogreLight = renderManager->addLightNode(this);
    }
    else {
		std::cerr << "ERROR: Se requiere un componente Transform para generar un Light\n";
	}
    return ogreLight != nullptr;
}

void Light::setEnabled(bool newActive) {
    Component::setEnabled(newActive);
    if (newActive) {
        ogreLight = renderManager->addLightNode(this);
    }
    else {
        renderManager->removeNode(ogreLight);
        ogreLight = nullptr;
    }
}


const int& Light::getType() const {
    return type;
}

