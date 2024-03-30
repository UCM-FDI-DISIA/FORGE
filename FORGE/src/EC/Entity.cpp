#include "Entity.h"
#include "Component.h"
#include "Factory.h"
#include "ComponentData.h"
#include "Transform.h"

Entity::Entity() : 
    fact(*Factory::getInstance()),
    scene(nullptr),
    components(),
    parent(nullptr),
    children(),
    groupId(0),
    alive(false) {
}

Entity::~Entity() { 
    for (auto& component : components) {
        delete component.second;
    }
}

void Entity::setContext(Scene* _scene, int _groupId) {
    scene = _scene;
    groupId = _groupId;
    alive = true;
}

bool Entity::isAlive() {
    return alive; 
}

void Entity::setAlive(bool _alive) {
    alive = _alive;
}

Component* Entity::addComponent(std::string id) {
    Component* component = fact.generateComponent(id);
    removeComponent(id);
    components.insert(std::pair<std::string, Component*>(id, component));
    component->setContext(this, scene);
    return component;
}

Component* Entity::addComponent(ComponentData* data) {
    Component* component = addComponent(data->getId());
    component->initSerialized(data);
    component->initComponent(data);
    return component;
}

Entity* Entity::addChild(Entity* child) {
    children.insert(child);
    child->setParent(this);
    return child;
}

Entity* Entity::removeChild(Entity* child) {
    children.erase(child);
    return child;
}

Entity* Entity::setParent(Entity* newParent) {
    if (parent != nullptr) {
        parent->removeChild(this);
    }
    parent = newParent;
    if (hasComponent("Transform") && parent->hasComponent("Transform")) {
        getComponent<Transform>()->setParent(parent->getComponent<Transform>());
    }
    return parent;
}

void Entity::removeComponent(std::string id) {
    auto iter = components.find(id);
    if (iter != components.end()) {
        delete iter->second;
        components.erase(iter);
    }
}

bool Entity::hasComponent(std::string id) {
    return components.count(id);
}

int Entity::getGroup() {
    return groupId;
}

void Entity::update() {
	for (auto& componentPair : components) {
        Component* component = componentPair.second;
        if(component->isEnabled()) {
		    component->update();
        }
	}
}

void Entity::fixedUpdate() {
	for (auto& componentPair : components) {
		Component* component = componentPair.second;
		if (component->isEnabled()) {
			component->fixedUpdate();
		}
	}
}

void Entity::setEnabled(bool enabled) {
    for (auto& componentPair : components) {
        Component* component = componentPair.second;
        component->setEnabled(enabled);
    }
}