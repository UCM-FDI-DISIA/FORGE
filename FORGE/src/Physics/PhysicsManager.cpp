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

    DebugMode* draw = new DebugMode();
    draw->setDebugMode(draw->getDebugMode()
                      | btIDebugDraw::DBG_DrawWireframe);
    world->setDebugDrawer(draw);

    world->setGravity(btVector3((btScalar)0, (btScalar)-9.8 , (btScalar)0));
    world->debugDrawWorld();
}

void PhysicsManager::updatePhysics() {
    world->stepSimulation(1 / 50.f, 20);
}

void PhysicsManager::changeGravity(forge::Vector3 newGravity) {
    world->setGravity(newGravity.operator btVector3());
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
    btQuaternion quat = forQuat.operator btQuaternion();
    btVector3 vect = forVect.operator btVector3();
    btDefaultMotionState* motionState = new btDefaultMotionState(btTransform(quat,vect));
    
    btRigidBody::btRigidBodyConstructionInfo bodyCI = 
        btRigidBody::btRigidBodyConstructionInfo(body->getMass(), motionState, body->getShape(), bodyInertia);
    /*/bodyCI.m_startWorldTransform = btTransform(
        btQuaternion(forQuat.getX(), forQuat.getY(), forQuat.getZ(), forQuat.getAngle()),
        btVector3(forVect.getX(), forVect.getY(), forVect.getZ()
        ));*/

    
    btRigidBody* rigidBody = new btRigidBody(bodyCI);
    if (body->isStatic()) {
        rigidBody->setCollisionFlags(rigidBody->getCollisionFlags() | btCollisionObject::CF_STATIC_OBJECT);
    }
    transforms.insert({rigidBody, body->getEntity()->getComponent<Transform>() });

    
    /*rigidBody->setWorldTransform(btTransform(
        btQuaternion(forQuat.getX(), forQuat.getY(), forQuat.getZ(), forQuat.getAngle()),
        btVector3(forVect.getX(), forVect.getY(), forVect.getZ())
    ));*/
    body->setRigidBody(rigidBody);
    world->addRigidBody(rigidBody);
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
