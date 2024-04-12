#include "PhysicsManager.h"
#include <Entity.h>
#include <Component.h>
#include <EntityData.h>
#include <lua.hpp>
#include <LuaBridge/LuaBridge.h>
#include <Scene.h>
#include "SceneManager.h"
#include "RigidBody.h"
#include <Transform.h>
#include "DebugMode.h"
#include <RenderManager.h>

#define BIT(x) (1<<(x))

std::unique_ptr<PhysicsManager> PhysicsManager::instance = nullptr;
bool PhysicsManager::initialised = false;

PhysicsManager::PhysicsManager() {
    broadphase = nullptr;
    collisionConfiguration = nullptr;
    dispatcher = nullptr;
    solver = nullptr;
    world = nullptr;
    debugger = nullptr;
    debugMode = true;
    collisionMatrix = std::unordered_map<std::string, std::unordered_map<std::string, bool>>();
}



PhysicsManager::~PhysicsManager() {
    if (debugger != nullptr) {
        delete debugger;
    }
    delete world;
    delete solver;
    delete dispatcher;
    delete collisionConfiguration;
    delete broadphase;
}

void PhysicsManager::Init() {
    instance = std::unique_ptr<PhysicsManager>(new PhysicsManager());
    initialised = true;
}

PhysicsManager* PhysicsManager::GetInstance() {
    if (initialised) return instance.get();
    return nullptr;
}

bool PhysicsManager::setup() {
    try {
        broadphase = new btDbvtBroadphase();
        collisionConfiguration = new btDefaultCollisionConfiguration();
        dispatcher = new btCollisionDispatcher(collisionConfiguration);
        solver = new btSequentialImpulseConstraintSolver();
        world = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);

        debugger = new DebugMode(RenderManager::GetInstance()->getSceneManager());
        // Son flags, se pueden añadir varios modos (ej. DBG_DrawWireFrame|DBG...)
        debugger->setDebugMode(btIDebugDraw::DBG_DrawWireframe);
        world->setDebugDrawer(debugger);

        world->setGravity(btVector3((btScalar)0, (btScalar)-9.8, (btScalar)0));
        collisionLayers["NOTHING"] = 0;
        collisionLayers["ALL"] = BIT(1);
        collisionMatrix["ALL"]["ALL"] = true;
        numberOfLayers = 2;
        return true;
    }
    catch (std::exception e) {
        return false;
    }
}

void PhysicsManager::drawDebug() {
    if (debugMode) {
        world->debugDrawWorld();
    }
}

void PhysicsManager::updatePhysics() {
    world->stepSimulation(1 / 50.f, 20);    
    handleCollisions();    
}

void PhysicsManager::handleCollisions() {
    //Iteramos en todos los manifolds ocurridos en la ultima simulacion
    int numManifolds = dispatcher->getNumManifolds();

    for (int i = 0; i < numManifolds; i++) {
        //Obtenemos el manifold actual
        btPersistentManifold* contactManifold = dispatcher->getManifoldByIndexInternal(i);
        const btCollisionObject* obA = contactManifold->getBody0();
        const btCollisionObject* obB = contactManifold->getBody1();
        //Iteramos en todos los contactos de cada manifold
        int numContacts = contactManifold->getNumContacts();
        for (int j = 0; j < numContacts; j++) {
            btManifoldPoint& pt = contactManifold->getContactPoint(j);
            if (pt.getDistance() < 0.f) {
                const btVector3& ptA = pt.getPositionWorldOnA();
                const btVector3& ptB = pt.getPositionWorldOnB();
                const btVector3& normalOnB = pt.m_normalWorldOnB;
            }
            //Llamamos a los callbacks que tenga guardados el componente Rigidbody de cada objeto
            auto auxTransformA = transforms.find((btRigidBody*)obA);
            auto auxTransformB = transforms.find((btRigidBody*)obB);
            if (auxTransformA != transforms.end() && auxTransformB != transforms.end()) {
                if (auxTransformA->second->getEntity()->hasComponent("Collider")) {
                    auxTransformA->second->getEntity()->getComponent<Collider>()->onCollision(auxTransformB->second->getEntity());
                }
                else {
                    auxTransformA->second->getEntity()->getComponent<RigidBody>()->onCollision(auxTransformB->second->getEntity());
                }

                if (auxTransformB->second->getEntity()->hasComponent("Collider")) {
                    auxTransformB->second->getEntity()->getComponent<Collider>()->onCollision(auxTransformA->second->getEntity());
                }
                else {
                    auxTransformB->second->getEntity()->getComponent<RigidBody>()->onCollision(auxTransformB->second->getEntity());
                }
            }
        }
    }
}

void PhysicsManager::changeGravity(forge::Vector3 newGravity) {
    world->setGravity(newGravity.operator btVector3());
}

void PhysicsManager::registerBody(btRigidBody* body, Transform* transform, std::string layer) {
    transforms.insert({ body,transform });
    int bitmask;
    for (auto layersToCollide : collisionMatrix[layer]) {
        bitmask |= collisionLayers[layersToCollide.first];
    }
    world->addRigidBody(body,collisionLayers[layer], bitmask);
}


void PhysicsManager::createImportantBody(RigidBody* body, std::string name) {
    registerBody(body->getRigidBody(), body->getEntity()->getComponent<Transform>());
    importantObjects.insert({ name,body->getRigidBody()});
    
}

void  PhysicsManager::deleteBody(btRigidBody* body) {
    auto auxTransform = transforms.find(body);
    world->removeRigidBody((*auxTransform).first);
    delete(*auxTransform).first->getMotionState();
    delete(*auxTransform).first->getCollisionShape();
    delete (*auxTransform).first;
    transforms.erase(auxTransform);
}

void PhysicsManager::setDebug(bool enabled) {
    debugMode = enabled;
}

bool PhysicsManager::isDebugModeEnabled() {
    return debugMode;
}



bool PhysicsManager::addLayer(const std::string layerName) {
    if (collisionLayers.count(layerName) == 0) {
        numberOfLayers++;
        collisionLayers[layerName] = BIT(numberOfLayers);
        collisionMatrix["ALL"][layerName] = true;
        return true;
    }
    return false;
}

void PhysicsManager::setCollideWith(const std::string layer, const std::vector<std::string>& layersToCollide) {
    if (collisionLayers.count(layer) > 0) {
        for (std::string aux : layersToCollide) {
                collisionMatrix[layer][aux] = true;
                collisionMatrix[aux][layer] = true;
        }
    }
}
