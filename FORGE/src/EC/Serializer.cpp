#include "Serializer.h"
#include "lua.hpp"
#include "LuaBridge/LuaBridge.h"

BaseSerialized::BaseSerialized(std::string myName) :
    name(myName) {
}

void Serializer::initialize(luabridge::LuaRef& data) {
    for (auto& e : *this) {
        e->initialize(data);
    }
}

Serializer::~Serializer() {
    for (auto& e : *this) {
        delete e;
    }
}