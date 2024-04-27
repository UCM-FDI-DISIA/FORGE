#include "Factory.h"

std::unique_ptr<Factory> Factory::instance = nullptr;

Factory* Factory::GetInstance() {
    if (instance.get() != nullptr) return instance.get();
    return (instance = std::unique_ptr<Factory>(new Factory())).get();
}

Component* Factory::generateComponent(std::string const& id) {
    auto iter = find(id);
    if (iter != end()) {
        return iter->second();
    }
    return nullptr;
}

void Factory::cleanUp() {
    for (auto it = begin(); it != end(); it = erase(it));
}

int Factory::getComponentAmount() {
    return componentOrder.size();
}

int Factory::getComponentOrder(std::string componentId) {
    return componentOrder[componentId];
}


