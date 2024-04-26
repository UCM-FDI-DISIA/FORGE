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
	handler(other.handler) {
	for (auto const& component : other.componentMap) {
		componentMap.insert({ component.first, new ComponentData(*component.second) });
	}
	for (auto const& child : other.children) {
		children.push_back(new EntityData(*child));
	}
}

EntityData::~EntityData() {
	for (auto& component : componentMap) {
		delete component.second;
	}
	for (auto& child : children) {
		if (!child->isBlueprint) { 
			delete child;
		}
	}
}