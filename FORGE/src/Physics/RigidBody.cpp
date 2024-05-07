#include "RigidBody.h"
#pragma warning(push)
#pragma warning(disable : 26495)
#include <btBulletDynamicsCommon.h>
#pragma warning(pop)
#include "PhysicsManager.h"
#include "Entity.h"
#include "Transform.h"
#include "Serializer.h"

#define PI 3.14159265358979323846264338327950288

const std::string RigidBody::id = "RigidBody";

RigidBody::RigidBody() :
    mass(1),
    kinematic(false),
    friction(0),
    restitution(0),
    staticBody(false),
    myGravity(1),
    axisBlockedPos(3, false),
    axisBlockedRot(3, false) {
    serializer(mass, "mass");
    serializer(friction, "friction");
    serializer(restitution, "restitution");
    serializer(staticBody, "static");
    serializer(myGravity, "gravity");
    serializer(axisBlockedPos, "axisBlockedPos");
    serializer(axisBlockedRot, "axisBlockedRot");
}


bool RigidBody::initComponent(ComponentData* data) {
    // En caso de que la masa sea negativa, se pone a 0
    if (mass < 0.0f || staticBody) {
        mass = 0.0f;
    }
    if (!createRigidBody(myShapeString, mass, staticBody, true)) {
        throwError(false, "No se pudo crear el componente Collider.");
    }
    setTrigger(trigger);

    return true;
}

bool RigidBody::createRigidBody(std::string const& myShapeType, float mass, bool isStatic, bool disableDeactivation) {
    if (!Collider::createRigidBody(myShapeType, mass, isStatic, disableDeactivation)) {
        throwError(false, "No se pudo crear el RigidBody.");
    }

    myBody->setRestitution((btScalar)restitution);
    myBody->setFriction((btScalar)friction);
    lockPosition(axisBlockedPos[0], axisBlockedPos[1], axisBlockedPos[2]);
    lockRotation(axisBlockedRot[0], axisBlockedRot[1], axisBlockedRot[2]);
    
    myBody->setGravity(physicsManager->fromForgeToBtVect(myGravity * physicsManager->getGravity()));

    return true;
}

void RigidBody::onEnabled() {
    createRigidBody(myShapeString, mass, staticBody, true);
    btTransform trans;
    trans.setOrigin(btVector3(lastPosition.getX(), lastPosition.getY(), lastPosition.getZ()));
    trans.setRotation(physicsManager->fromForgeToBtQuat(lastOrientation));
    myBody->setWorldTransform(trans);
    myBody->applyCentralForce(physicsManager->fromForgeToBtVect(lastForce));
}

void RigidBody::applyForce(forge::Vector3 const& force) {
    myBody->applyCentralForce({force.getX(), force.getY(), force.getZ()});
}

void RigidBody::clearForces() {
    myBody->clearForces();
}

void RigidBody::setGravity(forge::Vector3 const& newGravity) {
    myGravity = newGravity;
    myBody->setGravity(physicsManager->fromForgeToBtVect(newGravity * physicsManager->getGravity()));
}

void RigidBody::rest() {
	myBody->setLinearVelocity(btVector3(0, 0, 0));
	myBody->setAngularVelocity(btVector3(0, 0, 0));
}

void RigidBody::lockPosition(bool x, bool y, bool z) {
    axisBlockedPos[0] = x;
    axisBlockedPos[1] = y;
    axisBlockedPos[2] = z;

    btVector3 posConstr = btVector3(!axisBlockedPos[0], !axisBlockedPos[1], !axisBlockedPos[2]);
    myBody->setLinearFactor(posConstr);
}

void RigidBody::lockRotation(bool x, bool y, bool z) {
    axisBlockedRot[0] = x;
    axisBlockedRot[1] = y;
    axisBlockedRot[2] = z;

    btVector3 rotConstr = btVector3(!axisBlockedRot[0], !axisBlockedRot[1], !axisBlockedRot[2]);
    myBody->setAngularFactor(rotConstr);
}

void RigidBody::setFriction(float newFriction) {
    friction = newFriction;
    myBody->setFriction(friction);
}

void RigidBody::setRestitution(float newRestitution) {
    restitution = newRestitution;
    myBody->setRestitution(restitution);
}

void RigidBody::setRigidScale(forge::Vector3 const& scale) {
    myScale = scale;
    myShape->setLocalScaling(physicsManager->fromForgeToBtVect(bodyTransform->getGlobalScale() * myScale));
}

void RigidBody::setLinearVelocity(forge::Vector3 const& newVelocity) {
	myBody->setLinearVelocity(physicsManager->fromForgeToBtVect(newVelocity));
}

void RigidBody::setAngularVelocity(forge::Vector3 const& newVelocity) {
	myBody->setAngularVelocity(physicsManager->fromForgeToBtVect(newVelocity));
}

void RigidBody::setPosition(forge::Vector3 const& vect) {
    btTransform trans;
    btTransform prevTransform = myBody->getWorldTransform();
    trans.setOrigin(btVector3(vect.getX(), vect.getY(), vect.getZ()));
    trans.setRotation(prevTransform.getRotation());
    myBody->setWorldTransform(trans);
}

void RigidBody::setPositionX(float newX) {
    btTransform trans;
    btTransform prevTransform = myBody->getWorldTransform();
    trans.setOrigin(btVector3(newX, prevTransform.getOrigin().y(), prevTransform.getOrigin().z()));
    trans.setRotation(prevTransform.getRotation());
    myBody->setWorldTransform(trans);
}

void RigidBody::setPositionY(float newY) {
    btTransform trans;
    btTransform prevTransform = myBody->getWorldTransform();
    trans.setOrigin(btVector3(prevTransform.getOrigin().x(), newY, prevTransform.getOrigin().z()));
    trans.setRotation(prevTransform.getRotation());
    myBody->setWorldTransform(trans);
}

void RigidBody::setPositionZ(float newZ) {
    btTransform trans;
    btTransform prevTransform = myBody->getWorldTransform();
    trans.setOrigin(btVector3(prevTransform.getOrigin().x(), prevTransform.getOrigin().y(), newZ));
    trans.setRotation(prevTransform.getRotation());
    myBody->setWorldTransform(trans);
}

void RigidBody::rotateX(float newAngle) {
    btScalar aux = newAngle * (float)PI / 180;
    btTransform trans;
    btTransform prevTransform = myBody->getWorldTransform();
    trans.setOrigin(prevTransform.getOrigin());
    trans.setRotation(prevTransform.getRotation()* btQuaternion(btVector3(1, 0, 0), aux));
    myBody->setWorldTransform(trans);
}

void RigidBody::rotateY(float newAngle) {
    btScalar aux = newAngle * (float)PI / 180;
    btTransform trans;
    btTransform prevTransform = myBody->getWorldTransform();
    trans.setOrigin(prevTransform.getOrigin());
    trans.setRotation(prevTransform.getRotation() * btQuaternion(btVector3(0, 1, 0), aux));
    myBody->setWorldTransform(trans);
}

void RigidBody::rotateZ(float newAngle) {
    btScalar aux = newAngle * (float)PI / 180;
    btTransform trans;
    btTransform prevTransform = myBody->getWorldTransform();
    trans.setOrigin(prevTransform.getOrigin());
    trans.setRotation(prevTransform.getRotation() * btQuaternion(btVector3(0, 0, 1), aux));
    myBody->setWorldTransform(trans);
}

float RigidBody::getMass() {
    return mass;
}

forge::Vector3 RigidBody::getGravity() {
    return physicsManager->fromBtVectToForge(myBody->getGravity());
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

btCollisionShape* RigidBody::getShape() {
    return myShape;
}

forge::Vector3 RigidBody::getRigidScale() {
    return myScale;
}

float RigidBody::getSpeed() {
    return myBody->getTotalForce().length();
}

forge::Vector3 RigidBody::getLinearVelocity() {
    return physicsManager->fromBtVectToForge(myBody->getLinearVelocity());
}

forge::Vector3 RigidBody::getAngularVelocity() {
    return physicsManager->fromBtVectToForge(myBody->getAngularVelocity());
}