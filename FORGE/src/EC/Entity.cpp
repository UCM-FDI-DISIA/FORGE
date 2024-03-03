#include "Entity.h"
#include "Component.h"
#include "Factory.h"
#include "ComponentData.h"

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
    for (auto& c : components) {
        delete c.second;
    }
    for (auto& c : children) {
        delete c;
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

Component* Entity::addComponent(ComponentData* data) {
    Component* c = fact.generateComponent(data->getId());
    removeComponent(data->getId());
    components.insert(std::pair<std::string, Component*>(data->getId(), c));
    c->setContext(this, scene);
    c->initSerialized(data);
    c->initComponent(data);
    return c;
}

Entity* Entity::addChild(Entity* child) {
    children.insert(child);
    child->setParent(this);
    return child;
}

Entity* Entity::removeChild(Entity* child) {
    children.erase(child);
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

void Entity::removeComponent(std::string name) {
    auto iter = components.find(name);
    if (iter != components.end()) {
        delete iter->second;
        components.erase(iter);
    }
}

bool Entity::hasComponent(std::string name) {
    return components.count(name);
}

int Entity::getGroup() {
    return groupId;
}

void Entity::update() {
	for (auto& c : components) {
        Component* cmp = c.second;
        if(cmp->isEnabled()) {
		    cmp->update();
        }
	}
}

void Entity::fixedUpdate() {
	for (auto& c : components) {
		Component* cmp = c.second;
		if (cmp->isEnabled()) {
			cmp->fixedUpdate();
		}
	}
}
