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
    renderManager->removeNode(ogreLight);
}

bool Light::initComponent(ComponentData* data) {
    if(entity->hasComponent("Transform")) {
        renderManager = RenderManager::getInstance();
        ogreLight = renderManager->addLightNode(this);
    }
    return ogreLight != nullptr;
}

const int& Light::getType() const {
    return type;
}

