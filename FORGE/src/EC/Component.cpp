#include "Component.h"
#include "Serializer.h"

Component::Component() : 
    entity(nullptr),
    scene(nullptr),
    enabled(false),
    serializer(*(new Serializer())) {
}

Component::~Component() {
    delete& serializer;
}

void Component::setContext(Entity* _entity, Scene* _scene) {
    entity = _entity;
    scene = _scene;
    enabled = true;
}

bool Component::initSerialized(ComponentData* data) {
    try {
        serializer.initialize(*data);
        return true;
    }
    catch (std::exception e) {
        std::cerr << "ERROR: Fallo en el serializado de lua\n";
        return false;
    }
    
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
