#include "EntityData.h"
#include <lua.hpp>
#include <LuaBridge/LuaBridge.h>

EntityData::~EntityData() {
	for (auto& cmp : components) {
		delete cmp.second;
	}
}