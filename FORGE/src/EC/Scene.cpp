﻿#include "Scene.h"
#include "Entity.h"
#include "SceneManager.h"

Scene::Scene() :
    entitiesByGroup(SceneManager::GetInstance()->getMaxGroupId()),
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

FORGE_API Entity* Scene::addEntity(Entity* entity) {
    entitiesByGroup[entity->getGroup()].push_back(entity);
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
        return nullptr;
    }
    return iter->second;
}

bool Scene::setHandler(std::string const& handler, Entity* entity) {
    return handlers.insert(std::pair<std::string, Entity*>(handler, entity)).second;
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