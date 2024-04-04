#include "Light.h"
#include "RenderManager.h"
#include "Entity.h"
#include "Serializer.h"
#pragma warning(push)
#pragma warning(disable : 4251)
#pragma warning(disable : 26439)
#pragma warning(disable : 26451)
#pragma warning(disable : 26495)
#include <OgreLight.h>
#pragma warning(pop)

const std::string Light::id = "Light";

std::string const& Light::Id() {
    return id;
}

Light::Light() :
    ogreLight(nullptr),
    renderManager(nullptr) {
    serializer(type, "type");
}

Light::~Light() {
    renderManager->removeNode(ogreLight);
}

void Light::initComponent(ComponentData* data) {
    if(entity->hasComponent("Transform")) {
        renderManager = RenderManager::getInstance();
        ogreLight = renderManager->addLightNode(this);
    }
}

const int& Light::getType() const {
    return type;
}

