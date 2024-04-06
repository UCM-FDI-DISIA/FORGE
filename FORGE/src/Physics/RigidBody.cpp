#include "RigidBody.h"
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
    serializer(myScale, "scale");
    serializer(mass, "mass");
    serializer(friction, "friction");
    serializer(restitution, "restitution");
}

RigidBody::~RigidBody() {
    physicsManager->deleteBody(myBody);
}

void RigidBody::initComponent(ComponentData* data) {
    std::string myShapeType;
    // En caso de que la masa sea negativa, se pone a 0
    if (mass < 0) mass = 0; 
    myShapeType = data->get<std::string>("shapeType");
    staticBody = data->get<bool>("static");
    if (staticBody) mass = 0;

    // De forma predeterminada, el rigid es una caja
     shapeType = boxShape; 
     myShape = new btBoxShape(btVector3(myScale.getX(), myScale.getY(), myScale.getZ()));

    if (myShapeType == "Sphere") {
        shapeType = ballShape;
        myShape = new btSphereShape(myScale.getX()/2);
    }
    else if (myShapeType == "Capsule") {
        shapeType = capsuleShape;
        myShape = new btCapsuleShape(myScale.getX() / 2, myScale.getY());
    }
    else if (myShapeType == "Cilinder") {
        shapeType = cilinderShape;
        myShape = new btCylinderShape(myScale.operator btVector3());
    }
    physicsManager = PhysicsManager::getInstance();

    myBody = physicsManager->createBody(this);
    myBody->setRestitution((btScalar)restitution);
    myBody->setFriction((btScalar)friction);
}

void RigidBody::fixedUpdate() {
    if (entity->hasComponent("Transform")) {
        Transform* transform = entity->getComponent<Transform>();
        forge::Vector3 pos = forge::Vector3(
            myBody->getWorldTransform().getOrigin()
        );
        transform->setPosition(pos);
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

void RigidBody::registerCallback(CollisionCallback callback) {
    collisionCallbacks.push_back(callback);
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
    // Ninguna escala puede ser 0
    if (scale.getX() > 0 && scale.getY() > 0 && scale.getZ() > 0 
        && (shapeType==boxShape||shapeType==cilinderShape)) { 
        delete myShape;
        if (shapeType == boxShape) {
            myShape= myShape = new btBoxShape(btVector3(scale.getX(), scale.getY(), scale.getZ()));
        }
        else if (shapeType == cilinderShape)         {
            myShape = myShape = new btCylinderShape(btVector3(scale.getX(), scale.getY(), scale.getZ()));
        }
        myBody->setCollisionShape(myShape);
    }
}

void RigidBody::setRigidScale(float radius) {
    // Ninguna escala puede ser 0
    if (shapeType == ballShape && radius > 0) {
        delete myShape;
        myShape = new btSphereShape(radius);
        myBody->setCollisionShape(myShape);
    }
}

void RigidBody::setRigidScale(float radius, float height) {
    // Ninguna escala puede ser 0
    if (shapeType == capsuleShape && radius > 0 && height > 0) {
        delete myShape;
        myShape = new btCapsuleShape(radius,height);
        myBody->setCollisionShape(myShape);
    }
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

bool RigidBody::isStatic() {
    return staticBody;
}

bool RigidBody::isTrigger() {
    return trigger;
}

void RigidBody::setTrigger(bool isTrigger) {
    trigger = isTrigger;
    if (trigger)
		myBody->setCollisionFlags(myBody->getCollisionFlags() | btCollisionObject::CF_NO_CONTACT_RESPONSE);
	else
        myBody->setCollisionFlags(myBody->getCollisionFlags() & ~btCollisionObject::CF_NO_CONTACT_RESPONSE);
    
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

void RigidBody::onCollision(Entity* other) {
    for (auto cb : collisionCallbacks) {
        cb(this, other->getComponent<RigidBody>());
    }
}


