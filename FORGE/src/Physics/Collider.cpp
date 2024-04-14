#include "Collider.h"

#include "PhysicsManager.h"
#include "Entity.h"
#include <Transform.h>
#include <Serializer.h>
#include <btBulletDynamicsCommon.h>


const std::string Collider::id = "Collider";

Collider::Collider() :
    physicsManager(nullptr), myBody(nullptr)
    , myShape(nullptr),shapeType(boxShape), 
    trigger(false),collisionLayer("") {
    serializer(myScale, "scale");
    serializer(trigger, "trigger");
    serializer(collisionLayer, "layer");
}

Collider::~Collider() {
    physicsManager->deleteBody(myBody);
}

bool Collider::initComponent(ComponentData* data) {
    myShapeString = data->get<std::string>("shapeType");
    createRigidBody(myShapeString);
    return true;
}

void Collider::createRigidBody(std::string myShapeType) {
    if (entity->hasComponent<Transform>()) {
        physicsManager = PhysicsManager::GetInstance();
        // De forma predeterminada, el rigid es una caja
        shapeType = boxShape;
        myShape = new btBoxShape(btVector3(myScale.getX(), myScale.getY(), myScale.getZ()));

        if (myShapeType == "Sphere") {
            delete myShape;
            shapeType = ballShape;
            myShape = new btSphereShape(myScale.getX() / 2);
        }
        else if (myShapeType == "Capsule") {
            delete myShape;
            shapeType = capsuleShape;
            myShape = new btCapsuleShape(myScale.getX() / 2, myScale.getY());
        }
        else if (myShapeType == "Cilinder") {
            delete myShape;
            shapeType = cilinderShape;
            myShape = new btCylinderShape(myScale.operator btVector3());
        }

        //Inicializamos el rigid body
        forge::Quaternion forQuat = forge::Quaternion(0, 0, 0, 0);
        forge::Vector3 forVect = forge::Vector3(0, 0, 0);
        // En caso de que no se pueda acceder al transform, se usa un default
        Transform* aux = entity->getComponent<Transform>();
        if (aux != nullptr) {
            forQuat = aux->getRotation();
            forVect = aux->getGlobalPosition();
        }
        else {
            std::cerr << "ERROR: No se pudo acceder al Transform desde el Collider\n";
        }

        btQuaternion quat = forQuat.operator btQuaternion();
        btVector3 vect = forVect.operator btVector3();

        btVector3 bodyInertia;
        myShape->calculateLocalInertia(0, bodyInertia);
        btDefaultMotionState* motionState = new btDefaultMotionState(btTransform(quat, vect));

        btRigidBody::btRigidBodyConstructionInfo bodyCI =
            btRigidBody::btRigidBodyConstructionInfo(0, motionState, myShape, bodyInertia);


        btRigidBody* rigidBody = new btRigidBody(bodyCI);
        rigidBody->setCollisionFlags(rigidBody->getCollisionFlags() | btCollisionObject::CF_STATIC_OBJECT);

        bodyTransform = entity->getComponent<Transform>();

        myBody = rigidBody;

        physicsManager->registerBody(rigidBody, entity->getComponent<Transform>(), collisionLayer==""? "ALL":collisionLayer);
    }
    else{
        reportError("Se requiere un componente Transform para generar un Collider");
    }
}

void Collider::fixedUpdate() {
    if (bodyTransform != nullptr) {
        btTransform aux;
        myBody->getMotionState()->getWorldTransform(aux);
        forge::Vector3 pos;
        pos.setX(aux.getOrigin().x());
        pos.setY(aux.getOrigin().y());
        pos.setZ(aux.getOrigin().z());
        bodyTransform->setPosition(pos);

        forge::Quaternion quat = myBody->getOrientation();
        bodyTransform->setRotation(quat);
    }
}

void Collider::onEnabled() {
    createRigidBody(myShapeString);
    btTransform trans;
    trans.setOrigin(btVector3(lastPosition.getX(),lastPosition.getY(),lastPosition.getZ()));
    trans.setRotation(lastOrientation.operator btQuaternion());
    myBody->setWorldTransform(trans);
    myBody->applyCentralForce(lastForce);
}

void Collider::onDisabled() {
    lastForce = forge::Vector3(myBody->getTotalForce().x(), myBody->getTotalForce().y(), myBody->getTotalForce().z());
    physicsManager->deleteBody(myBody);
    lastPosition = bodyTransform->getPosition();
    lastOrientation = bodyTransform->getRotation();
}

bool Collider::hasCollidedWith(Collider* other) {
    return myBody->checkCollideWith(other->getBody());
}

void Collider::registerCallback(CollisionCallback callback) {
    collisionCallbacks.push_back(callback);
}

void Collider::onCollision(Entity* other) {
    for (auto cb : collisionCallbacks) {
        cb(this, other->getComponent<Collider>());
    }
}

void Collider::setTrigger(bool isTrigger) {
    trigger = isTrigger;
    if (trigger) {
        myBody->setCollisionFlags(myBody->getCollisionFlags() | btCollisionObject::CF_NO_CONTACT_RESPONSE);
    }
    else {
        myBody->setCollisionFlags(myBody->getCollisionFlags() & ~btCollisionObject::CF_NO_CONTACT_RESPONSE);
    }
}

bool Collider::isTrigger() {
    return trigger;
}

btRigidBody* Collider::getBody() {
    return myBody;
}

std::string Collider::getLayer() {
    return collisionLayer;
}
