#include "EntityData.h"
#include "ComponentData.h"

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