#include "Serializer.h"
#include "lua.hpp"
#include "LuaBridge/LuaBridge.h"

Component::Serializer::BaseSerialized::BaseSerialized(std::string myName) :
    name(myName) {
}

void Component::Serializer::initialize(ComponentData& data) {
    for (auto& serialized : serializations) {
        serialized->initialize(data);
    }
}

Component::Serializer::~Serializer() {
    for (auto& serialized : serializations) {
        delete serialized;
    }
}