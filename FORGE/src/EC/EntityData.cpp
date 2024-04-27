#include "EntityData.h"
#include "ComponentData.h"


EntityData::EntityData() :
	isBlueprint(false),
	keepBetweenScenes(false),
	group(""),
	handler("") {
}

EntityData::EntityData(EntityData const& other) :
	isBlueprint(false),
	group(other.group),
	keepBetweenScenes(other.keepBetweenScenes),
	handler(other.handler) {
	for (auto const& component : other.components) {
		components.insert({ component.first, new ComponentData(*component.second) });
	}
	for (auto const& child : other.children) {
		children.push_back(new EntityData(*child));
	}
}

EntityData::~EntityData() {
	for (auto& component : components) {
		delete component.second;
	}
	for (auto& child : children) {
		if (!child->isBlueprint) { 
			delete child;
		}
	}
}