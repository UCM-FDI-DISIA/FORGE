#include "Collider.h"

#include "PhysicsManager.h"
#include "Entity.h"
#include <Transform.h>
#include <Serializer.h>


const std::string Collider::id = "Collider";

Collider::Collider() :
    physicsManager(nullptr), myBody(nullptr)
    , myShape(nullptr),shapeType(boxShape), 
    trigger(false) {
    serializer(myScale, "scale");
    serializer(trigger, "trigger");
}

Collider::~Collider() {
    physicsManager->deleteBody(myBody);
}

bool Collider::initComponent(ComponentData* data) {
    std::string myShapeType;
    // En caso de que la masa sea negativa, se pone a 0
   
    myShapeType = data->get<std::string>("shapeType");

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
    physicsManager = PhysicsManager::GetInstance();

    //Inicializamos el rigid body

    btVector3 bodyInertia;
    Transform* aux = entity->getComponent<Transform>();
    forge::Quaternion forQuat = forge::Quaternion(0, 0, 0, 0);
    forge::Vector3 forVect = forge::Vector3(0, 0, 0);
    // En caso de que no se pueda acceder al transform, se usa un default
    forQuat = aux->getRotation();
    forVect = aux->getGlobalPosition();

    btQuaternion quat = forQuat.operator btQuaternion();
    btVector3 vect = forVect.operator btVector3();
    myShape->calculateLocalInertia(0, bodyInertia);
    btDefaultMotionState* motionState = new btDefaultMotionState(btTransform(quat, vect));

    btRigidBody::btRigidBodyConstructionInfo bodyCI =
        btRigidBody::btRigidBodyConstructionInfo(0, motionState, myShape, bodyInertia);


    btRigidBody* rigidBody = new btRigidBody(bodyCI);
    rigidBody->setCollisionFlags(rigidBody->getCollisionFlags() | btCollisionObject::CF_STATIC_OBJECT);

    Transform* bodyTransform = entity->getComponent<Transform>();
    if (bodyTransform == nullptr) {
        // Si no existe transform, se coloca uno vacio
        entity->addComponent("Transform");
        bodyTransform = entity->getComponent<Transform>();
    }

    myBody = rigidBody;

    physicsManager->registerBody(rigidBody, entity->getComponent<Transform>());

    return true;
}

void Collider::fixedUpdate() {
    if (entity->hasComponent("Transform")) {
        Transform* transform = entity->getComponent<Transform>();
        forge::Vector3 pos = forge::Vector3(myBody->getWorldTransform().getOrigin());
        transform->setPosition(pos);
        forge::Quaternion quat = myBody->getOrientation();
        transform->setRotation(quat);
    }
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