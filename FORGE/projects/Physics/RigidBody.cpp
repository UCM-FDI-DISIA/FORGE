#include "PhysicsManager.h"
#include "Entity.h"
#include <Transform.h>
#include <Serializer.h>


const std::string RigidBody::id = "RigidBody";

RigidBody::RigidBody() :
    physicsManager(nullptr), mass(0)
    , kinematic(false), myBody(nullptr) 
    , myShape(nullptr), friction(0), restitution(0)
    , shapeType(boxShape) {
    myScale = forge::Vector3(0, 0, 0);
    serializer(mass, "mass");
    serializer(friction, "friction");
    serializer(restitution, "restitution");
}

RigidBody::~RigidBody() {
    physicsManager->deleteBody(myBody);
}

void RigidBody::initComponent(ComponentData* data) {
    if (entity->hasComponent("Transform")) {
        physicsManager = PhysicsManager::getInstance();
        myBody = physicsManager->createBody(this);
    }
    std::string shapeType;
    shapeType = data->get<std::string>("shapeType");
    if (shapeType == "Box") {
        shapeType = boxShape;
        forge::Vector3 forVect = entity->getComponent<Transform>()->getGlobalScale();
        myScale = forVect;
        myShape = new btBoxShape(btVector3(forVect.getX(),forVect.getY(),forVect.getZ()));
    }
    else if (shapeType == "Ball") {
        shapeType = ballShape;
        forge::Vector3 forVect = entity->getComponent<Transform>()->getGlobalScale();
        myScale = forge::Vector3(forVect.getX(), forVect.getX(), forVect.getX());
        myShape = new btSphereShape(forVect.getX()/2);
    }
}

void RigidBody::fixedUpdate() {
    if (entity->hasComponent("Transform")) {
        Transform* transform = entity->getComponent<Transform>();
        transform->setPosition((forge::Vector3(myBody->getCenterOfMassPosition().getX(), myBody->getCenterOfMassPosition().getY(), myBody->getCenterOfMassPosition().getZ())));
        
        forge::Quaternion quat = myBody->getOrientation();
        transform->setRotation(quat);
    }
}

void RigidBody::applyForce(forge::Vector3 force) {
    myBody->applyCentralForce({force.getX(), force.getY(), force.getZ()});
}

void RigidBody::applyGravity() {
    myBody->applyGravity();
}

void RigidBody::clearForces() {
    myBody->clearForces();
}

bool RigidBody::hasCollidedWith(RigidBody* other) {
    return myBody->checkCollideWith(other->getBody());
}

void RigidBody::setFriction(float newFriction) {
    
    friction = newFriction;
    myBody->setFriction(friction);
}

void RigidBody::setRestitution(float newRestitution) {
    restitution = newRestitution;
    myBody->setRestitution(restitution);
}

void RigidBody::setRigidBody(btRigidBody* body) {
    myBody = body;
    myShape = body->getCollisionShape();
}

void RigidBody::setRigidScale(forge::Vector3 scale) {
    if (shapeType == boxShape) {
        delete myShape;
        myShape= myShape = new btBoxShape(btVector3(scale.getX(), scale.getY(), scale.getZ()));
        myBody->setCollisionShape(myShape);
    }
    // Maybe devolver un error si es esfera
}

void RigidBody::setRigidScale(float radius) {
    if (shapeType == ballShape) {
        delete myShape;
        myShape = new btSphereShape(radius);
        myBody->setCollisionShape(myShape);
    }
    // Maybe devolver un error si es cubo
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

forge::Vector3 RigidBody::getRigidScale() {
    return myScale;
}

btRigidBody* RigidBody::getBody(){
    return myBody;
}


