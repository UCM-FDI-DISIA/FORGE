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
	std::unordered_map<std::string, ComponentData*> components;
	std::vector<EntityData*> children;
	/// <summary>
	/// Elimina los ComponentData y los EntityData hijos de este que no sean blueprint.
	/// </summary>
	~EntityData();
};
#endif