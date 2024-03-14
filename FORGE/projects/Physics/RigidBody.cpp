#include "RigidBody.h"
#include "PhysicsManager.h"
#include "Entity.h"

const std::string RigidBody::id = "RigidBody";

RigidBody::RigidBody() :
    physicsManager(nullptr), mass(0)
    , kinematic(false), myBody(nullptr) 
    , myShape(nullptr), friction(0), restitution(0) {

}

RigidBody::~RigidBody() {
    physicsManager->deleteBody(myBody);
}

void RigidBody::initComponent(ComponentData* data) {
    if (entity->hasComponent("Transform")) {
        physicsManager = PhysicsManager::getInstance();
        myBody = physicsManager->createBody(this);
    }
}

void RigidBody::setMass(float newMass) {
    
    mass = newMass;
    physicsManager->updateMass(myBody, mass);
}

void RigidBody::setFriction(float newFriction) {
    
    friction = newFriction;
    myBody->setFriction(friction);
}

void RigidBody::setRestitution(float newRestitution) {
    restitution = newRestitution;
    myBody->setRestitution(restitution);
}

float RigidBody::getMass() {
    return mass;
}

float RigidBody::getFriction() {
    return friction;
}

float RigidBody::getRestitution() {
    return restitution;
}

btCollisionShape* RigidBody::getShape() {
    return myShape;
}


