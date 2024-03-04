#include "ComponentData.h"
#include "SceneManager.h"

ComponentData::ComponentData(std::string compId) :
    id(compId),
    data(new luabridge::LuaRef(luabridge::newTable(SceneManager::getInstance()->getLuaState()))) {        
}

ComponentData::ComponentData(std::string compId, luabridge::LuaRef* lrData) :
    id(compId),
    data(lrData) {
}

ComponentData::~ComponentData() {
    delete data;
}

std::string ComponentData::getId() {
    return id;
}