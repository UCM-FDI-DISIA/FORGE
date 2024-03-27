#include "Serializer.h"
#include <lua.hpp>
#pragma warning(push)
#pragma warning(disable : 26439)
#include <LuaBridge/LuaBridge.h>
#pragma warning(pop)

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