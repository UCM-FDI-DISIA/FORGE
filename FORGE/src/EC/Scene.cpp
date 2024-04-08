#include "Scene.h"
#include "Entity.h"
#include "SceneManager.h"

Scene::Scene() :
    entitiesByGroup(SceneManager::GetInstance()->getMaxGroupId()),
    handlers() {
    //for (auto & group : entitiesByGroup) {
    //    group.reserve(500); //Reserva espacio para cada lista @TODO: Leer el maximo de entidades por grupo a un parametro en un archivo de configuracion
    //}
}

Scene::~Scene() {
    for (auto& group : entitiesByGroup) {
        for (auto& entity : group) {
            delete entity;
            entity = nullptr;
        }
    }
}

void Scene::update() {
    refresh();
    for (auto& group : entitiesByGroup) {
        for (auto& entity : group) {
            entity->update();
        }
    }
    
}

void Scene::fixedUpdate() {
    for (auto& group : entitiesByGroup) {
        for (auto& entity : group) {
            entity->fixedUpdate();
        }
    }
}

void Scene::refresh() {
    for (auto& group : entitiesByGroup) {
        group.erase(
            std::remove_if(group.begin(), group.end(),
                [](Entity* entity) {
                    if (entity->isAlive()) {
                        return false;
                    }
                    else {
                        delete entity;
                        return true;
                    }
                }),
            group.end());
    }
}

Entity* Scene::addEntity(int groupId) {
    Entity* entity = new Entity();
    entity->setAlive(true);
    entity->setContext(this, groupId);
	entitiesByGroup[groupId].push_back(entity);
    return entity;
}

const std::vector<Entity*>& Scene::getEntitiesByGroup(int groupId) {
    if(groupId < 0 || groupId > SceneManager::GetInstance()->getMaxGroupId()){
        return entitiesByGroup[0];
    }
    return entitiesByGroup[groupId];
}

Entity* Scene::getEntityByHandler(std::string const& handler) {
    auto iter = handlers.find(handler);
    if (iter == handlers.end()) {
        return nullptr;
    }
    return iter->second;
}

bool Scene::setHandler(std::string const& handler, Entity* entity) {
    return handlers.insert(std::pair<std::string, Entity*>(handler, entity)).second;
}

void Scene::endScene() {
    sceneEnd = true;
}

bool Scene::getEndScene() {
    return sceneEnd;
}
void Scene::setEnabled(bool enabled) {
    for (auto& group : entitiesByGroup) {
        for (auto& entity : group) {
            entity->setEnabled(enabled);
        }
    }
}