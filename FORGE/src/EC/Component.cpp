#include "Component.h"
#include "Serializer.h"
#include "SceneManager.h"

Component::Component() : 
    entity(nullptr),
    scene(nullptr),
    enabled(false),
    serializer(*new Serializer()),
    sceneManager(*SceneManager::GetInstance()){
}

Component::~Component() {
    delete &serializer;
}

void Component::setContext(Entity* _entity, Scene* _scene) {
    entity = _entity;
    scene = _scene;
}

bool Component::initSerialized(ComponentData* data) {
    try {
        serializer.initialize(*data);
    }
    catch (std::exception e) {
        throwError(false, "Fallo en el serializado de lua");
    }
    enabled = true;
    return true;
}

bool Component::initComponent(ComponentData* data) { return true; }

void Component::update() {}

void Component::fixedUpdate() {}

void Component::setEnabled(bool _enabled) {
    if (!enabled && _enabled) {
        onEnabled();
    }
    else if (enabled && !_enabled) {
        onDisabled();
    }
    enabled = _enabled;
}

void Component::onEnabled() {

}

void Component::onDisabled() {

}

bool Component::isEnabled() const {
    return enabled;
}

Entity* Component::getEntity() const {
    return entity;
}

Scene* Component::getScene() const {
    return scene;
}
