#include "PhysicsManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Entity.h"
#include "Component.h"
#include "EntityData.h"
#include "lua.hpp"
#include "LuaBridge/LuaBridge.h"
#include "RigidBody.h"
#include "Transform.h"

std::unique_ptr<PhysicsManager> PhysicsManager::instance = nullptr;


PhysicsManager::PhysicsManager() {
    broadphase = nullptr;
    collisionConfiguration = nullptr;
    dispatcher = nullptr;
    solver = nullptr;
    world = nullptr;
}

void PhysicsManager::initPhysics() {
    broadphase = new btDbvtBroadphase();
    collisionConfiguration = new btDefaultCollisionConfiguration();
    dispatcher = new btCollisionDispatcher(collisionConfiguration);
    solver = new btSequentialImpulseConstraintSolver();
    world = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);

    world->setGravity(btVector3(0, -9.8, 0));
}

PhysicsManager* PhysicsManager::getInstance() {
    if (instance.get() != nullptr) {
        return instance.get();
    }
	return (instance = std::unique_ptr<PhysicsManager>(new PhysicsManager())).get();
}
btRigidBody* PhysicsManager::createBody(RigidBody* body) {
    btVector3 bodyInertia;
    body->getShape()->calculateLocalInertia(body->getMass(), bodyInertia);
    forge::Quaternion forQuat = body->getEntity()->getComponent<Transform>()->getRotation();
    forge::Vector3 forVect = body->getEntity()->getComponent<Transform>()->getGlobalPosition();
    btQuaternion quat = btQuaternion(forQuat.getX(), forQuat.getY(), forQuat.getZ(), forQuat.getAngle());
    btVector3 vect = btVector3(forVect.getX(), forVect.getY(), forVect.getZ());
    btDefaultMotionState* motionState = new btDefaultMotionState(btTransform(quat,vect));
    
    btRigidBody::btRigidBodyConstructionInfo bodyCI = 
        btRigidBody::btRigidBodyConstructionInfo(body->getMass(), motionState, body->getShape(), bodyInertia);
    transforms.insert({new btRigidBody(bodyCI), body->getEntity()->getComponent<Transform>() });

    btRigidBody* rigidBody = new btRigidBody(bodyCI);
    body->setRigidBody(rigidBody);
    return rigidBody;
}
btRigidBody* PhysicsManager::createImportantBody(RigidBody* body, std::string name) {
    btRigidBody* auxBody = createBody(body);
    importantObjects.insert({ name,auxBody });
    return auxBody;
}

void  PhysicsManager::deleteBody(btRigidBody* body) {
    auto auxTransform = transforms.find(body);
    delete (*auxTransform).second;
    transforms.erase(auxTransform);
}
