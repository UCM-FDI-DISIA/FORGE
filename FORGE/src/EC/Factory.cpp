#include "Factory.h"

std::unique_ptr<Factory> Factory::instance = nullptr;

Factory* Factory::getInstance() {
    if (instance.get() != nullptr) return instance.get();
    return (instance = std::unique_ptr<Factory>(new Factory())).get();
}

bool Factory::registerComponent(std::string id, std::function<Component*()> generator) {
    return insert(std::pair<std::string, std::function<Component*()>>(id, generator)).second;
}

Component* Factory::generateComponent(std::string id) {
    auto iter = find(id);
    if (iter != end()) {
        return iter->second();
    }
    return nullptr;
}