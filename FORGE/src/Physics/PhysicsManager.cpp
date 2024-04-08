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

std::unique_ptr<PhysicsManager> PhysicsManager::instance = nullptr;

PhysicsManager::PhysicsManager() {
    broadphase = nullptr;
    collisionConfiguration = nullptr;
    dispatcher = nullptr;
    solver = nullptr;
    world = nullptr;
    debugger = nullptr;
    debugMode = true;
}

PhysicsManager::~PhysicsManager() {
    if(debugger!=nullptr)delete debugger;
    delete world;
    delete solver;
    delete dispatcher;
    delete collisionConfiguration;
    delete broadphase;
}



void PhysicsManager::initPhysics() {
    broadphase = new btDbvtBroadphase();
    collisionConfiguration = new btDefaultCollisionConfiguration();
    dispatcher = new btCollisionDispatcher(collisionConfiguration);
    solver = new btSequentialImpulseConstraintSolver();
    world = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);

    debugger = new DebugMode(RenderManager::GetInstance()->getSceneManager());
    // Son flags, se pueden añadir varios modos (ej. DBG_DrawWireFrame|DBG...)
    debugger->setDebugMode(btIDebugDraw::DBG_DrawWireframe); 
    world->setDebugDrawer(debugger);

    world->setGravity(btVector3((btScalar)0, (btScalar)-9.8 , (btScalar)0));
}

void PhysicsManager::drawDebug() {
    world->debugDrawWorld();
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
                //std::cout << "Collision at: " << ptA.getX() << " " << ptA.getY() << " " << ptA.getZ() << std::endl;
                //std::cout << "Collision at: " << ptB.getX() << " " << ptB.getY() << " " << ptB.getZ() << std::endl;
                //std::cout << "Collision normal: " << normalOnB.getX() << " " << normalOnB.getY() << " " << normalOnB.getZ() << std::endl;
            }
            //Llamamos a los callbacks que tenga guardados el componente Rigidbody de cada objeto
            auto auxTransformA = transforms.find((btRigidBody*)obA);
            auto auxTransformB = transforms.find((btRigidBody*)obB);
            if (auxTransformA != transforms.end() && auxTransformB != transforms.end()) {
                auxTransformA->second->getEntity()->getComponent<RigidBody>()->onCollision(auxTransformB->second->getEntity());

                auxTransformB->second->getEntity()->getComponent<RigidBody>()->onCollision(auxTransformA->second->getEntity());
            }
        }
    }
}

void PhysicsManager::changeGravity(forge::Vector3 newGravity) {
    world->setGravity(newGravity.operator btVector3());
}

PhysicsManager* PhysicsManager::GetInstance() {
    if (instance.get() != nullptr) {
        return instance.get();
    }
	return (instance = std::unique_ptr<PhysicsManager>(new PhysicsManager())).get();
}

void PhysicsManager::registerBody(btRigidBody* body, Transform* transform) {
    transforms.insert({ body,transform });
    world->addRigidBody(body);
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