#include "Component.h"
class luabridge::LuaRef;

Component::Component() : 
    entity(nullptr),
    scene(nullptr),
    enabled(false) {
}

Component::~Component() {}

void Component::setContext(Entity* _entity, Scene* _scene) {
    entity = _entity;
    scene = _scene;
    enabled = true;
}

void Component::initComponent(luabridge::LuaRef* data) {}


void Component::update() {}

void Component::fixedUpdate() {}

void Component::setEnabled(bool _enabled) {
    enabled = _enabled;
}

bool Component::isEnabled() {
    return enabled;
}