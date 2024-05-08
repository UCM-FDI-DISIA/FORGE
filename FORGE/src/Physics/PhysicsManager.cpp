#include "PhysicsManager.h"
#pragma warning(push)
#pragma warning(disable : 26495)
#include <btBulletDynamicsCommon.h>
#pragma warning(pop)
#include "RenderManager.h"
#include "Entity.h"
#include "RigidBody.h"
#include "Transform.h"
#include "DebugMode.h"
#include "Collider.h"
#include "ContactCallback.h"
#include "TimeForge.h"
#include "ForgeError.h"

#define BIT(x) (1<<(x))

std::unique_ptr<PhysicsManager> PhysicsManager::instance = nullptr;
bool PhysicsManager::initialised = false;

PhysicsManager::PhysicsManager() :
    broadphase(new btDbvtBroadphase()),
    collisionConfiguration(new btDefaultCollisionConfiguration()),
    dispatcher(new btCollisionDispatcher(collisionConfiguration)),
    solver(new btSequentialImpulseConstraintSolver()),
    world(new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration)),
    #ifdef _DEBUG
    debugger(nullptr),
    debugMode(true),
    #endif // _DEBUG
    collisionMatrix(),
    numberOfLayers(0) {
}

PhysicsManager::~PhysicsManager() {
    #ifdef _DEBUG
    if (debugger != nullptr) {
        delete debugger;
    }
    #endif // _DEBUG
    delete world;
    delete solver;
    delete dispatcher;
    delete collisionConfiguration;
    delete broadphase;
}

bool PhysicsManager::Init() {
    if (initialised) {
        throwError(false, "Manager de fisicas ya inicializado.");
    }
    instance = std::unique_ptr<PhysicsManager>(new PhysicsManager());

    initialised = true;
    return true;
}

PhysicsManager* PhysicsManager::GetInstance() {
    if (initialised) return instance.get();
    return nullptr;
}

bool PhysicsManager::setup() {
    #ifdef _DEBUG
    // Son flags, se pueden añadir varios modos (ej. DBG_DrawWireFrame|DBG...)
    debugger = new DebugMode(RenderManager::GetInstance()->getSceneManager());
    debugger->setDebugMode(btIDebugDraw::DBG_DrawWireframe);
    world->setDebugDrawer(debugger);
    if (debugMode && !debugger->init()) {
        throwError(false, "No se pudo inicializar el debugger de fisicas");
    }
    #endif // DEBUG
        
    world->setGravity(btVector3(0.0f, -9.8f, 0.0f));
    collisionLayers["NOTHING"] = 0;
    collisionLayers["ALL"] = BIT(1);
    collisionMatrix["ALL"]["ALL"] = true;
    numberOfLayers = 2;
}

void PhysicsManager::updatePhysics() {
    world->stepSimulation(static_cast<btScalar>(forge::Time::fixedDeltaTime), 0, static_cast<btScalar>(forge::Time::fixedDeltaTime));
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
            if (pt.getDistance() < 0.0f) {
                const btVector3& ptA = pt.getPositionWorldOnA();
                const btVector3& ptB = pt.getPositionWorldOnB();
                const btVector3& normalOnB = pt.m_normalWorldOnB;
            }
            //Llamamos a los callbacks que tenga guardados el componente Rigidbody de cada objeto
            auto auxTransformA = transforms.find((btRigidBody*)obA);
            auto auxTransformB = transforms.find((btRigidBody*)obB);
            if (auxTransformA != transforms.end() && auxTransformB != transforms.end()) {
                if (auxTransformA->second->getEntity()->hasComponent(Collider::id)) {
                    auxTransformA->second->getEntity()->getComponent<Collider>()->onCollision(auxTransformB->second->getEntity());
                }
                else if (auxTransformA->second->getEntity()->hasComponent(RigidBody::id)) {
                    auxTransformA->second->getEntity()->getComponent<RigidBody>()->onCollision(auxTransformB->second->getEntity());
                }

                if (auxTransformB->second->getEntity()->hasComponent(Collider::id)) {
                    auxTransformB->second->getEntity()->getComponent<Collider>()->onCollision(auxTransformA->second->getEntity());
                }
                else if (auxTransformB->second->getEntity()->hasComponent(RigidBody::id)) {
                    auxTransformB->second->getEntity()->getComponent<RigidBody>()->onCollision(auxTransformA->second->getEntity());
                }
            }
        }
    }

    //Iteramos en todos los colliders para manejar los fines de colision
    for (auto& t : transforms) {
        if (t.second->getEntity()->hasComponent(Collider::id)) {
            t.second->getEntity()->getComponent<Collider>()->checkCollisionEnd();
        }
        else if (t.second->getEntity()->hasComponent(RigidBody::id)) {
            t.second->getEntity()->getComponent<RigidBody>()->checkCollisionEnd();
        }
    }

}

void PhysicsManager::changeGravity(forge::Vector3 const& newGravity) {
    world->setGravity(fromForgeToBtVect(newGravity));
}

forge::Vector3 PhysicsManager::getGravity() const {
    return fromBtVectToForge(world->getGravity());
}

void PhysicsManager::registerBody(btRigidBody* body, Transform* transform, std::string const& layer) {
    transforms.insert({ body,transform });
    int bitmask = 0;
    for (auto& layersToCollide : collisionMatrix[layer]) {
        bitmask |= collisionLayers[layersToCollide.first];
    }
    world->addRigidBody(body,collisionLayers[layer], bitmask);
}


void PhysicsManager::createImportantBody(RigidBody* body, std::string const& name) {
    registerBody(body->getBody(), body->getEntity()->getComponent<Transform>());
    importantObjects.insert({ name,body->getBody()});
    
}

void  PhysicsManager::deleteBody(btRigidBody* body) {
    auto auxTransform = transforms.find(body);
    if (auxTransform != transforms.end()) {
        world->removeRigidBody(auxTransform->first);
        delete auxTransform->first->getMotionState();
        delete auxTransform->first->getCollisionShape();
        delete auxTransform->first;
        transforms.erase(auxTransform);
    }
}

#ifdef _DEBUG
void PhysicsManager::drawDebug() {
    if (debugMode) {
        world->debugDrawWorld();
    }
}

void PhysicsManager::setDebug(bool enabled) {
    debugMode = enabled;
}

bool PhysicsManager::isDebugModeEnabled() const {
    return debugMode;
}
#endif // _DEBUG

bool PhysicsManager::addLayer(std::string const& layerName) {
    if (collisionLayers.count(layerName) != 0) {
        throwError(false, "Ya se habia registrado la capa");
    }
    ++numberOfLayers;
    collisionLayers[layerName] = BIT(numberOfLayers);
    collisionMatrix["ALL"][layerName] = true;
    collisionMatrix[layerName]["ALL"] = true;
    return true;
}

bool PhysicsManager::setCollideWith(std::string const& layer, std::vector<std::string> const& layersToCollide) {
    if (collisionLayers.count(layer) == 0) {
        throwError(false, "No habia layers registradas");
    }
    for (std::string const& aux : layersToCollide) {
        auto layer1 = collisionMatrix.find(layer);
        auto layer2 = collisionMatrix.find(aux);
        if (layer1 == collisionMatrix.end() || layer2 == collisionMatrix.end()) {
            throwError(false, "No se pudo registrar la colision (capas invalidas)");
        }
        layer1->second[aux] = true;
        layer2->second[layer] = true;
    }
    
    return true;
}

bool PhysicsManager::checkContact(btRigidBody* body1, btRigidBody* body2) {
    ContactCallback callback;
    world->contactPairTest(body1, body2, callback);
    return callback.contacting();
}

btVector3 PhysicsManager::fromForgeToBtVect(forge::Vector3 const& vect) const {
    return btVector3(vect.getX(),vect.getY(),vect.getZ());
}

forge::Vector3 PhysicsManager::fromBtVectToForge(btVector3 const& vect) const {
    return forge::Vector3(vect.getX(),vect.getY(),vect.getZ());
}

btQuaternion PhysicsManager::fromForgeToBtQuat(forge::Quaternion const& quat) const {
    return btQuaternion(quat.getX(),quat.getY(),quat.getZ(),quat.getW());
}

forge::Quaternion PhysicsManager::fromBtQuatToForge(btQuaternion const& quat) const {
    return forge::Quaternion(quat.getX(), quat.getY(), quat.getZ(), quat.getW());
}
