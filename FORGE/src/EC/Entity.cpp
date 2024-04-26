#include "Entity.h"
#include "Component.h"
#include "Factory.h"
#include "ComponentData.h"
#include "Transform.h"

Entity::Entity() : 
    fact(*Factory::GetInstance()),
    scene(nullptr),
    components(),
    componentMap(),
    parent(nullptr),
    children(),
    groupId(0),
    alive(false),
    keepBetweenScenes(false) {
}

Entity::~Entity() {
    for (auto& component : components) {
        delete component;
    }
    for (auto& child : children) {
        child->setAlive(false);
    }
    if (parent != nullptr) {
       // parent->removeChild(this);
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

Component* Entity::addComponent(std::string const& id) {
    Component* component = fact.generateComponent(id);
    if (component == nullptr) {
        throwError(nullptr, "No existe un componente \"" << id << "\".\n");
    }
    removeComponent(id);
    components.push_back(component);
    componentMap.insert(std::pair<std::string, Component*>(id, component));
    component->setContext(this, scene);
    return component;
}

Component* Entity::addComponent(ComponentData* data) {
    Component* component = addComponent(data->getId());
    component->initSerialized(data);
    component->initComponent(data);
    return component;
}

FORGE_API bool Entity::initComponents(std::vector<ComponentData*> data)
{
    for (int i = 0; i < components.size(); ++i) {
        if (!components[i]->initComponent(data[i])) {
            return false;
        }
    }

    return true;
}

FORGE_API bool Entity::initSerializedComponents(std::vector<ComponentData*> data)
{
    for (int i = 0; i < components.size(); ++i) {
        if (!components[i]->initSerialized(data[i])) {
            return false;
        }
    }

    return true;
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
    if (hasComponent(Transform::id) && parent->hasComponent(Transform::id)) {
        getComponent<Transform>()->setParent(parent->getComponent<Transform>());
    }
    return parent;
}

void Entity::removeComponent(std::string const& id) {
    auto iter = componentMap.find(id);
    if (iter != componentMap.end()) {
        delete iter->second;
        componentMap.erase(iter);
    }
}

bool Entity::hasComponent(std::string const& id) {
    return componentMap.count(id);
}

int Entity::getGroup() {
    return groupId;
}

FORGE_API const std::unordered_set<Entity*>& Entity::getChildren() const {
    return children;
}

void Entity::update() {
    for (auto& component : components) {
        if (component->isEnabled()) {
		    component->update();
        }
	}
}

void Entity::fixedUpdate() {
    for (auto& component : components) {
		if (component->isEnabled()) {
			component->fixedUpdate();
		}
	}
}

void Entity::setEnabled(bool enabled) {
    for (auto& component : components) {
        component->setEnabled(enabled);
    }
}

FORGE_API bool Entity::isKeepBetweenScenes() {
    return keepBetweenScenes;
}

FORGE_API void Entity::setKeepBetweenScenes(bool ddol) {
    keepBetweenScenes = ddol;
}

FORGE_API void Entity::changeScene(Scene* newScene) {
    scene = this->scene;
    for (auto& component : components) {
        component->setContext(this, scene);
    }
}
