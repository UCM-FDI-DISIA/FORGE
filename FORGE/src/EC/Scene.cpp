#include "Scene.h"
#include "Entity.h"
#include "SceneManager.h"

Scene::Scene() :
    entitiesByGroup(SceneManager::getInstance()->getMaxGroupId()),
    handlers() {
    for (auto & grpEnts : entitiesByGroup) {
        grpEnts.reserve(500); //Reserva espacio para cada lista @TODO: Leer el maximo de entidades por grupo a un parametro en un archivo de configuracion
    }
}

Scene::~Scene() {
    for (auto& group : entitiesByGroup) {
        for (auto& e : group) {
            delete e;
            e = nullptr;
        }
    }
}

void Scene::update() {
    for (auto& group : entitiesByGroup) {
        for (auto& e : group) {
            e->update();
        }
    }

    refresh();
}

void Scene::fixedUpdate() {
    for (auto& group : entitiesByGroup) {
        for (auto& e : group) {
            e->fixedUpdate();
        }
    }
}

void Scene::render() const {

}

void Scene::refresh() {
    for (auto& grpEnts : entitiesByGroup) {
        grpEnts.erase(
            std::remove_if(grpEnts.begin(), grpEnts.end(),
                [](Entity* e) {
                    if (e->isAlive()) {
                        return false;
                    }
                    else {
                        delete e;
                        return true;
                    }
                }),
            grpEnts.end());
    }
}

Entity* Scene::addEntity(int groupId) {
    Entity* e = new Entity();
    e->setAlive(true);
    e->setContext(this, groupId);
	entitiesByGroup[groupId].push_back(e);
    return e;
}

const std::vector<Entity*>& Scene::getEntitiesByGroup(int groupId) {
    if(groupId < 0 || groupId > SceneManager::getInstance()->getMaxGroupId()){
        std::vector<Entity*> res = std::vector<Entity*>();
        return res;
    }
    return entitiesByGroup[groupId];
}

const Entity* Scene::getEntityByHandler(std::string handler) {
    auto handIt = handlers.find(handler);
    if (handIt == handlers.end()) {
        return nullptr;
    }
    return handIt->second;
}

bool Scene::setHandler(std::string handler, Entity* ent) {
    return handlers.insert(std::pair<std::string, Entity*>(handler, ent)).second;
}