#include "ComponentData.h"
#include "SceneManager.h"
#include <Vector3.h>

ComponentData::ComponentData(std::string _id) :
    id(_id),
    data(new luabridge::LuaRef(luabridge::newTable(SceneManager::getInstance()->getLuaState()))) {        
}

ComponentData::ComponentData(std::string _id, luabridge::LuaRef* _data) :
    id(_id),
    data(_data) {
}

ComponentData::~ComponentData() {
    delete data;
}

std::string ComponentData::getId() {
    return id;
}

bool ComponentData::has(std::string param)
{
    return !(*data)[param].isNil();
}
