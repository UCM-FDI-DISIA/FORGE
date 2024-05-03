#include "Collider.h"
#pragma warning(push)
#pragma warning(disable : 26495)
#include <btBulletDynamicsCommon.h>
#pragma warning(pop)
#include "PhysicsManager.h"
#include "Entity.h"
#include "Serializer.h"
#include "Transform.h"
#include "RigidBody.h"

const std::string Collider::id = "Collider";

Collider::Collider() :
    physicsManager(nullptr),
    myBody(nullptr),
    myShape(nullptr),
    shapeType(boxShape), 
    trigger(false),
    collisionLayer(""),
    bodyTransform(nullptr) {
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
    setTrigger(trigger);
    return true;
}

void Collider::createRigidBody(std::string const& myShapeType) {
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
            myShape = new btCylinderShape(physicsManager->fromForgeToBtVect(myScale));
        }

        //Inicializamos el rigid body
        forge::Quaternion forQuat = forge::Quaternion(0.0f, 0.0f, 0.0f, 1.0f);
        forge::Vector3 forVect = forge::Vector3(0.0f, 0.0f, 0.0f);
        // En caso de que no se pueda acceder al transform, se usa un default
        Transform* aux = entity->getComponent<Transform>();
        if (aux != nullptr) {
            forQuat = aux->getRotation();
            forVect = aux->getGlobalPosition();
        }
        else {
            reportError("No se pudo acceder al Transform desde el Collider");
        }

        btQuaternion quat = physicsManager->fromForgeToBtQuat(forQuat);
        btVector3 vect = physicsManager->fromForgeToBtVect(forVect);

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

        forge::Quaternion quat = physicsManager->fromBtQuatToForge(myBody->getOrientation());
        bodyTransform->setRotation(quat);
    }
}

void Collider::onEnabled() {
    createRigidBody(myShapeString);
    btTransform trans;
    trans.setOrigin(btVector3(lastPosition.getX(),lastPosition.getY(),lastPosition.getZ()));
    trans.setRotation(physicsManager->fromForgeToBtQuat(lastOrientation));
    myBody->setWorldTransform(trans);
    myBody->applyCentralForce(physicsManager->fromForgeToBtVect(lastForce));
}

void Collider::onDisabled() {
    lastForce = forge::Vector3(myBody->getTotalForce().x(), myBody->getTotalForce().y(), myBody->getTotalForce().z());
    physicsManager->deleteBody(myBody);
    lastPosition = bodyTransform->getPosition();
    lastOrientation = bodyTransform->getRotation();
}

bool Collider::hasCollidedWith(Entity* other) {

    if (other->hasComponent<RigidBody>()) {
        return myBody->checkCollideWith(other->getComponent<RigidBody>()->getBody());
    }
    if (other->hasComponent<Collider>()) {
        return myBody->checkCollideWith(other->getComponent<Collider>()->getBody());
    }
    //Si no tiene ningun componente de colision, no ha colisionado.
    //Posiblemente haya algun problema aqui, si un componente sin collider ha llegado hasta aqui
    return false;
}

void Collider::registerCallback(callbackType type, std::function<void(Collider*, Collider*)> callback) {   
    switch (type) {
        case Collider::onCollisionEnter:
                onCollisionEnterCallbacks.push_back(callback);
            break;
        case Collider::onCollisionStay:
                oncollisionStayCallbacks.push_back(callback);
            break;
        case Collider::onCollisionLeave:
        		oncollisionLeaveCallbacks.push_back(callback);
            break;
    }
}

void Collider::onCollision(Entity* other) {

    //Si la entidad no esta en la lista de colisiones, se llama a los OnCollisionEnterCallbacks
    if (std::find(collidedEntities.begin(), collidedEntities.end(), other) == collidedEntities.end()) {
        for (auto& cb : onCollisionEnterCallbacks) {
			cb(this, other->getComponent<Collider>());
		}
		collidedEntities.push_back(other);
	}
	else { //Si la entidad esta en la lista de colisiones, se llama a los OnCollisionStayCallbacks
        for (auto& cb : oncollisionStayCallbacks) {
			cb(this, other->getComponent<Collider>());
		}
	}
}

void Collider::checkCollisionEnd() {
    std::list<Entity*> toDelete;
    for (auto entity : collidedEntities) {
        btRigidBody* otherBody = nullptr;
        
        if (entity->hasComponent<RigidBody>()) {
            otherBody = entity->getComponent<RigidBody>()->getBody();
        }
        else if (entity->hasComponent<Collider>()) {
            otherBody = entity->getComponent<Collider>()->getBody();
        } //Si no tiene ningun componente de colision, algo va MUY MAL


        if (!physicsManager->checkContact(myBody, otherBody)) {
            for (auto& cb : oncollisionLeaveCallbacks) {
				cb(this, entity->getComponent<Collider>());
			}
			toDelete.push_back(entity);
		}
	}
    for (auto entity : toDelete) {
		collidedEntities.remove(entity);
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

forge::Vector3 Collider::getPosition() {
    return physicsManager->fromBtVectToForge(myBody->getWorldTransform().getOrigin());
}
