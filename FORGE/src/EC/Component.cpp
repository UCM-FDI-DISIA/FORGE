#include "Component.h"
#include "lua.hpp"
#include "LuaBridge/LuaBridge.h"

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

Component::BaseSerialized::BaseSerialized(std::string myName) :
    name(myName) {
}

void Component::Serializer::initialize(luabridge::LuaRef& data) {
    for (auto& e : *this) {
        e->initialize(data);
    }
}

Component::Serializer::~Serializer() {
    for (auto& e : *this) {
        delete e;
    }
}

template<typename T>
void Component::Serialized<T>::initialize(luabridge::LuaRef& data) {
    if (!data[name].isNil()) {
        var = data[name].cast<T>();
    }
}