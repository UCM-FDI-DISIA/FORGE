#include "Scene.h"
#include "Entity.h"
#include "SceneManager.h"
#include "ForgeError.h"

Scene::Scene() :
    entitiesByGroup(SceneManager::GetInstance()->getMaxGroupId()),
    entitiesByGroupToAdd(SceneManager::GetInstance()->getMaxGroupId()),
    handlers() {

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
    for (auto& group : entitiesByGroup) {
        for (auto& entity : group) {
            entity->update();
        }
    }

    refresh();
}

void Scene::fixedUpdate() {
    for (auto& group : entitiesByGroup) {
        for (auto& entity : group) {
            entity->fixedUpdate();
        }
    }
}

void Scene::refresh() {

    for (auto& group : entitiesByGroupToAdd) {
        if (!group.empty()) {
            for (auto& entity : group) {
                entitiesByGroup[group[0]->getGroup()].push_back(entity);
            }
        }
    }

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
    for (auto& group : entitiesByGroupToAdd) {
        group.clear();
    }
}

Entity* Scene::addEntity(int groupId) {
    if (groupId >= SceneManager::GetInstance()->getMaxGroupId()) {
        throwError(nullptr, "No se pudo agregar la entidad, groupId no valida");
    }
    Entity* entity = new Entity();
    entity->setAlive(true);
    entity->setContext(this, groupId);
	entitiesByGroupToAdd[groupId].push_back(entity);
    return entity;
}

Entity* Scene::addEntity(Entity* entity) {
    entitiesByGroupToAdd[entity->getGroup()].push_back(entity);
    entity->changeScene(this);
    return entity;
}

std::vector<Entity*>& Scene::getEntitiesByGroup(int groupId) {
    if(groupId < 0 || groupId > SceneManager::GetInstance()->getMaxGroupId()){
        return entitiesByGroup[0];
    }
    return entitiesByGroup[groupId];
}

Entity* Scene::getEntityByHandler(std::string const& handler) {
    auto iter = handlers.find(handler);
    if (iter == handlers.end()) {
        throwError(nullptr, "No existe la entidad con el handler " + handler + " en la escena");
    }
    return iter->second;
}

bool Scene::setHandler(std::string const& handler, Entity* entity) {
    if (handlers.count(handler)) {
        throwError(false, "Ya existia una entidad con el handler " + handler + " en la escena.");
    }
    if (handlers.insert(std::pair<std::string, Entity*>(handler, entity)).second) {
        entity->setHandler(handler);
    }
    return false;
}


std::vector<Entity*> Scene::disableScene() {
    std::vector<Entity*> keptEntities;
    for (auto& group : entitiesByGroup) {
        for (auto iterator = group.begin(); iterator != group.end();) {
            Entity* entity = *iterator;
            if (entity->isKeepBetweenScenes()) {
                keptEntities.push_back(entity);
                iterator = group.erase(iterator);
            }
            else {
                entity->setEnabled(false);
                if (getEntityByHandler(entity->getHandler()) == entity) {
                    handlers.erase(entity->getHandler());
                }
                ++iterator;
            }
        }
    }
    return keptEntities;
}

void Scene::enableScene() {
    for (auto& group : entitiesByGroup) {
        for (auto& entity : group) {
            entity->setEnabled(true);
        }
    }
}