#pragma once
#ifndef ENTITY_DATA_H_
#define ENTITY_DATA_H_
#include <unordered_map>
#include <string>

namespace luabridge {
	class LuaRef;
}

struct EntityData {
	bool isBlueprint = false;
	std::string group = "";
	std::string handler = "";
	// Tiene que ser unordered map de punteros a LuaRef para funcionar el forwarding
	std::unordered_map<std::string, luabridge::LuaRef*> components;
	~EntityData();
};
#endif
