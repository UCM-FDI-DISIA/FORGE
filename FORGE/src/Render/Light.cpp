#include "Light.h"
#pragma warning(push)
#pragma warning(disable : 4251)
#pragma warning(disable : 26439)
#pragma warning(disable : 26451)
#pragma warning(disable : 26495)
#include <OgreLight.h>
#pragma warning(pop)
#include "RenderManager.h"
#include "Entity.h"
#include "Serializer.h"

const std::string Light::id = "Light";

Light::Light() :
    ogreLight(nullptr),
    renderManager(nullptr) {
    serializer(type, "type");
}

Light::~Light() {
    if(ogreLight != nullptr && renderManager != nullptr) {
        renderManager->removeNode(ogreLight);
    }
}

bool Light::initComponent(ComponentData* data) {
    if(entity->hasComponent("Transform")) {
        renderManager = RenderManager::GetInstance();
        ogreLight = renderManager->addLightNode(this);
    }
    else {
        reportError("Se requiere un componente Transform para generar un Light");
	}
    return ogreLight != nullptr;
}

void Light::onEnabled() {
    ogreLight = renderManager->addLightNode(this);
}

void Light::onDisabled() {
    renderManager->removeNode(ogreLight);
    ogreLight = nullptr;
}



const int& Light::getType() const {
    return type;
}

