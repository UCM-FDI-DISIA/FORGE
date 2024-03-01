#include "EntityData.h"
#include "ComponentData.h"

EntityData::~EntityData() {
	for (auto& cmp : components) {
		delete cmp.second;
	}
}