#include "Entity.h"
#include "Component.h"
#include "Factory.h"

Entity::Entity() : 
    scene(nullptr),
    components(),
    alive(false),
    groupId(0),
    fact(*Factory::getInstance()){
}

Entity::~Entity() { 
    for (auto iter = components.begin(); iter != components.end(); iter = components.erase(iter)) {
        delete iter->second;
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

Component* Entity::addComponent(/*LuaObject data*/) {
    //Component* c = fact.generateComponent(/*data.name*/);
    //removeComponent(/*data.name*/);
    //components.insert(std::pair<std::string, Component*>(/*data.name*/, c));
    //c->setContext(this, scene);
    //c->initComponent(/*data*/);
    //return c;
    return nullptr;
}

void Entity::removeComponent(std::string name) {
    if (components.count(name)) {
        delete components[name];
        components.erase(name);
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
