#include "EntityData.h"
#include "ComponentData.h"
#include "Factory.h"


EntityData::EntityData() :
	isBlueprint(false),
	group(""),
	handler(""),
	components(Factory::GetInstance()->getComponentAmount(), nullptr) {
}

EntityData::EntityData(EntityData const& other) :
	isBlueprint(false),
	group(other.group),
	handler(other.handler) {
	for (auto const& component : other.components) {
		ComponentData* newComp = nullptr;
		if (component != nullptr) {
			newComp = new ComponentData(*component);
		}
		components.push_back(newComp);
	}
	for (auto const& child : other.children) {
		children.push_back(new EntityData(*child));
	}
}

EntityData::~EntityData() {
	for (auto& component : components) {
		if (component != nullptr) {
			delete component;
		}
	}
	for (auto& child : children) {
		if (!child->isBlueprint) { 
			delete child;
		}
	}
}