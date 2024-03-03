#include "EntityData.h"
#include "ComponentData.h"

EntityData::~EntityData() {
	for (auto& cmp : components) {
		delete cmp.second;
	}
	for (auto& child : children) {
		if (!child->isBlueprint) { 
			delete child;
		}
	}
}