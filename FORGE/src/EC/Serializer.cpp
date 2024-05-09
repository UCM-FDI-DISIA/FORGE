#include "Serializer.h"
#include <lua.hpp>
#pragma warning(push)
#pragma warning(disable : 26439)
#pragma warning(disable : 26495)
#include <LuaBridge/LuaBridge.h>
#pragma warning(pop)

Component::Serializer::BaseSerialized::BaseSerialized(std::string const& myName) :
    name(myName) {
}

void Component::Serializer::BaseSerialized::initialize(ComponentData& data) {
}

void Component::Serializer::initialize(ComponentData& data) {
    for (auto& serialized : serializations) {
        serialized->initialize(data);
    }
}

Component::Serializer::Serializer() : 
    serializations() {
}

Component::Serializer::~Serializer() {
    for (auto& serialized : serializations) {
        delete serialized;
    }
}
