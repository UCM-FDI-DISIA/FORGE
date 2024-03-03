#pragma once
#ifndef ENTITY_DATA_H_
#define ENTITY_DATA_H_
#include <unordered_map>
#include <string>

class ComponentData;

struct EntityData {
	bool isBlueprint = false;
	std::string group = "";
	std::string handler = "";
	// Tiene que ser unordered map de punteros a LuaRef para funcionar el forwarding
	std::unordered_map<std::string, ComponentData*> components;
	std::vector<EntityData*> children;
	~EntityData();
};
#endif
