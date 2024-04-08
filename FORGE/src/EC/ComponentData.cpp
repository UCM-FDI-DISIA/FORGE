#include "ComponentData.h"
#include "SceneManager.h"
#include <Vector3.h>

ComponentData::ComponentData(std::string const& _id) :
    id(_id),
    data(new luabridge::LuaRef(luabridge::newTable(SceneManager::GetInstance()->getLuaState()))) {        
}

ComponentData::ComponentData(std::string const& _id, luabridge::LuaRef* _data) :
    id(_id),
    data(_data) {
}

ComponentData::~ComponentData() {
    delete data;
}

std::string const& ComponentData::getId() {
    return id;
}

bool ComponentData::has(std::string const& param)
{
    return !(*data)[param].isNil();
}
