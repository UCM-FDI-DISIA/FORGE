#include "RigidBody.h"
#include "PhysicsManager.h"
#include "Entity.h"
#include <Transform.h>
#include <Serializer.h>
#include "btBulletDynamicsCommon.h"
#define PI 3.14159265358979323846264338327950288

const std::string RigidBody::id = "RigidBody";

RigidBody::RigidBody() :
      mass(0)
    , kinematic(false), friction(0), restitution(0)
    , staticBody(false), myGravity(FLT_MAX, FLT_MAX, FLT_MAX) {
    axisBlocked = std::vector<bool>(6, false);
    serializer(mass, "mass");
    serializer(friction, "friction");
    serializer(restitution, "restitution");
    serializer(staticBody, "static");
    serializer(myGravity, "gravity");
    serializer(axisBlocked, "axisBlocked");
}


bool RigidBody::initComponent(ComponentData* data) {
    // En caso de que la masa sea negativa, se pone a 0
    if (mass < 0) {
        mass = 0;
    }
    myShapeString = data->get<std::string>("shapeType");
    if (staticBody) {
        mass = 0;
    }

    createRigidBody(myShapeString);

    return true;
}

void RigidBody::createRigidBody(std::string myShapeType) {
    if(entity->hasComponent<Transform>()) {
        physicsManager = PhysicsManager::GetInstance();
        // De forma predeterminada, el rigid es una caja
        shapeType = boxShape;
        myShape = new btBoxShape(btVector3(myScale.getX(), myScale.getY(), myScale.getZ()));

        if (myShapeString == "Sphere") {
            delete myShape;
            shapeType = ballShape;
            myShape = new btSphereShape(myScale.getX() / 2);
        }
        else if (myShapeString == "Capsule") {
            delete myShape;
            shapeType = capsuleShape;
            myShape = new btCapsuleShape(myScale.getX() / 2, myScale.getY());
        }
        else if (myShapeString == "Cilinder") {
            delete myShape;
            shapeType = cilinderShape;
            myShape = new btCylinderShape(myScale.operator btVector3());
        }

        //Inicializamos el rigid body
        forge::Quaternion forQuat = forge::Quaternion(0, 0, 0, 0);
        forge::Vector3 forVect = forge::Vector3(0, 0, 0);

        btQuaternion quat = forQuat.operator btQuaternion();
        btVector3 vect = forVect.operator btVector3();

        btVector3 bodyInertia;
        getShape()->calculateLocalInertia(getMass(), bodyInertia);
        btDefaultMotionState* motionState = new btDefaultMotionState(btTransform(quat, vect));

        btRigidBody::btRigidBodyConstructionInfo bodyCI =
            btRigidBody::btRigidBodyConstructionInfo(getMass(), motionState, getShape(), bodyInertia);

        myBody = new btRigidBody(bodyCI);
        if (isStatic()) {
            myBody->setCollisionFlags(myBody->getCollisionFlags() | btCollisionObject::CF_STATIC_OBJECT);
        }

        bodyTransform = entity->getComponent<Transform>();
        myBody->setActivationState(DISABLE_DEACTIVATION);

        physicsManager->registerBody(myBody, entity->getComponent<Transform>(),(collisionLayer=="")? "ALL" : collisionLayer);
        myBody->setRestitution((btScalar)restitution);
        myBody->setFriction((btScalar)friction);
        lockPosition(axisBlocked[0], axisBlocked[1], axisBlocked[2]);
        lockRotation(axisBlocked[3], axisBlocked[4], axisBlocked[5]);
        if (myGravity != forge::Vector3(FLT_MAX, FLT_MAX, FLT_MAX)) {
            myBody->setGravity(myGravity);
        }
	}
	else {
        reportError("Se requiere un componente Transform para generar un RigidBody");
	}
    
}

void RigidBody::applyForce(forge::Vector3 force) {
    myBody->applyCentralForce({force.getX(), force.getY(), force.getZ()});
}


void RigidBody::clearForces() {
    myBody->clearForces();
}

void RigidBody::lockPosition(bool x, bool y, bool z) {
    axisBlocked[0] = x;
    axisBlocked[1] = y;
    axisBlocked[2] = z;

    btVector3 posConstr = btVector3(!axisBlocked[0], !axisBlocked[1], !axisBlocked[2]);
    myBody->setLinearFactor(posConstr);
}

void RigidBody::lockRotation(bool x, bool y, bool z) {
    axisBlocked[3] = x;
    axisBlocked[4] = y;
    axisBlocked[5] = z;

    btVector3 rotConstr = btVector3(!axisBlocked[3], !axisBlocked[4], !axisBlocked[5]);
    myBody->setAngularFactor(rotConstr);
}

void RigidBody::setGravity(forge::Vector3 newGravity) {
    myGravity = newGravity;
    myBody->setGravity(newGravity.operator btVector3());
}

void RigidBody::setFriction(float newFriction) {
    friction = newFriction;
    myBody->setFriction(friction);
}

void RigidBody::setRestitution(float newRestitution) {
    restitution = newRestitution;
    myBody->setRestitution(restitution);
}

void RigidBody::setRigidScale(forge::Vector3 scale) {
    // Ninguna escala puede ser 0
    if (scale.getX() > 0 && scale.getY() > 0 && scale.getZ() > 0 
        && (shapeType==boxShape||shapeType==cilinderShape)) { 
        delete myShape;
        if (shapeType == boxShape) {
            myShape= myShape = new btBoxShape(btVector3(scale.getX(), scale.getY(), scale.getZ()));
        }
        else if (shapeType == cilinderShape) {
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

float RigidBody::getFriction() {
    return friction;
}

float RigidBody::getRestitution() {
    return restitution;
}

btRigidBody* RigidBody::getRigidBody() {
    return myBody;
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