#pragma once
#ifndef ECS_LOAD_H_
#define ECS_LOAD_H_
#include <string>
#include <vector>

class Lua;

struct ComponentStruct {
	std::string id;
	Lua* data;
};

struct EntityStruct {
	std::string group;
	std::string handler;
	std::vector<ComponentStruct*> components;
};

class EcsLoad {

};

#endif // !COMPONENT_H_