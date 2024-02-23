#include "Factory.h"

std::unique_ptr<Factory> Factory::instance = nullptr;

Factory* Factory::getInstance() {
    if (instance.get() != nullptr) return instance.get();
    return (instance = std::unique_ptr<Factory>(new Factory())).get();
}

bool Factory::registerComponent(std::string compName, std::function<Component*()> generator) {
    return insert(std::pair<std::string, std::function<Component*()>>(compName, generator)).second;
}

Component* Factory::generateComponent(std::string compName) {
    auto it = find(compName);
    if (it != end()) {
        return it->second();
    }
    return nullptr;
}