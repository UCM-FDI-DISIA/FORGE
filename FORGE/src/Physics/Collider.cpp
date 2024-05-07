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
    physicsManager(PhysicsManager::GetInstance()),
    myBody(nullptr),
    myShape(nullptr),
    shapeType(boxShape), 
    trigger(false),
    collisionLayer(""),
    bodyTransform(nullptr),
    myScale(1.0f) {
    serializer(myScale, "scale");
    serializer(trigger, "trigger");
    serializer(collisionLayer, "layer");
    serializer(myShapeString, "shapeType");
}

Collider::~Collider() {
    physicsManager->deleteBody(myBody);
}

bool Collider::initComponent(ComponentData* data) {
    if (!createRigidBody(myShapeString, 0.0f, true, false)) {
        throwError(false, "No se pudo crear el componente Collider.");
    }
    setTrigger(trigger);
    return true;
}

bool Collider::createRigidBody(std::string const& myShapeType, float mass, bool isStatic, bool disableDeactivation) {
    if (!entity->hasComponent<Transform>()) {
        throwError(false, "Se requiere un componente Transform para generar un Collider");
    }
    bodyTransform = entity->getComponent<Transform>();

    if (myShapeType == "Sphere") {
        shapeType = ballShape;
        myShape = new btSphereShape(0.5f);
    }
    else if (myShapeType == "Capsule") {
        shapeType = capsuleShape;
        myShape = new btCapsuleShape(0.5f, 1.0f);
    }
    else if (myShapeType == "Cylinder") {
        shapeType = cylinderShape;
        myShape = new btCylinderShape(btVector3(0.5f, 0.5f, 0.5f));
    }
    else /*Box*/ {
        // De forma predeterminada, el rigid es una caja
        shapeType = boxShape;
        myShape = new btBoxShape(btVector3(0.5f, 0.5f, 0.5f));
    }

    forge::Vector3 scale = bodyTransform->getGlobalScale() * myScale;
    myShape->setLocalScaling(physicsManager->fromForgeToBtVect(scale));

    //Inicializamos el rigid body
    forge::Quaternion forQuat = bodyTransform->getGlobalRotation();
    forge::Vector3 forVect = bodyTransform->getGlobalPosition();

    btQuaternion quat = physicsManager->fromForgeToBtQuat(forQuat);
    btVector3 vect = physicsManager->fromForgeToBtVect(forVect);

    btVector3 bodyInertia;
    myShape->calculateLocalInertia(mass, bodyInertia);
    btDefaultMotionState* motionState = new btDefaultMotionState(btTransform(quat, vect));

    btRigidBody::btRigidBodyConstructionInfo bodyCI =
        btRigidBody::btRigidBodyConstructionInfo(mass, motionState, myShape, bodyInertia);


    myBody = new btRigidBody(bodyCI);
    if (isStatic) {
        myBody->setCollisionFlags(myBody->getCollisionFlags() | btCollisionObject::CF_STATIC_OBJECT);
    }

    if (disableDeactivation) {
        myBody->setActivationState(DISABLE_DEACTIVATION);
    }

    physicsManager->registerBody(myBody, bodyTransform, (collisionLayer == "") ? "ALL" : collisionLayer);

    return true;
}

void Collider::fixedUpdate() {
    btTransform aux;
    myBody->getMotionState()->getWorldTransform(aux);
    forge::Vector3 pos;
    pos.setX(aux.getOrigin().x());
    pos.setY(aux.getOrigin().y());
    pos.setZ(aux.getOrigin().z());
    bodyTransform->setGlobalPosition(pos);

    forge::Quaternion quat = physicsManager->fromBtQuatToForge(myBody->getOrientation());
    bodyTransform->setGlobalRotation(quat);
}

void Collider::onEnabled() {
    createRigidBody(myShapeString, 0.0f, true, false);
    btTransform trans;
    trans.setOrigin(btVector3(lastPosition.getX(),lastPosition.getY(),lastPosition.getZ()));
    trans.setRotation(physicsManager->fromForgeToBtQuat(lastOrientation));
    myBody->setWorldTransform(trans);
    myBody->applyCentralForce(physicsManager->fromForgeToBtVect(lastForce));
}

void Collider::onDisabled() {
    lastForce = forge::Vector3(myBody->getTotalForce().x(), myBody->getTotalForce().y(), myBody->getTotalForce().z());
    physicsManager->deleteBody(myBody);
    lastPosition = bodyTransform->getGlobalPosition();
    lastOrientation = bodyTransform->getGlobalRotation();
}

bool Collider::hasCollidedWith(Entity* other) {

    if (other->hasComponent<RigidBody>()) {
        return physicsManager->checkContact(myBody, other->getComponent<RigidBody>()->getBody());   
    }
    if (other->hasComponent<Collider>()) {
        return physicsManager->checkContact(myBody, other->getComponent<Collider>()->getBody());
    }
    //Si no tiene ningun componente de colision, no ha colisionado.
    //Posiblemente haya algun problema aqui, si un componente sin collider/rigidbody ha llegado hasta aqui
    return false;
}

void Collider::registerCallback(forge::callbackType type, std::function<void(Collider*, Collider*)> callback) {   
    switch (type) {
        case forge::onCollisionEnter:
                onCollisionEnterCallbacks.push_back(callback);
            break;
        case forge::onCollisionStay:
                oncollisionStayCallbacks.push_back(callback);
            break;
        case forge::onCollisionLeave:
        		oncollisionLeaveCallbacks.push_back(callback);
            break;
    }
}

void Collider::onCollision(Entity* other) {
    //Si la entidad no esta en la lista de colisiones, se llama a los OnCollisionEnterCallbacks
    if (std::find(collidedEntities.begin(), collidedEntities.end(), other) == collidedEntities.end()) {
        for (auto& cb : onCollisionEnterCallbacks) {
            if (other->hasComponent(Collider::id)) {
                cb(this, other->getComponent<Collider>());
            }
            else if (other->hasComponent(RigidBody::id)) {
                cb(this, other->getComponent<RigidBody>());
            }
		}
		collidedEntities.push_back(other);
	}
	else { //Si la entidad esta en la lista de colisiones, se llama a los OnCollisionStayCallbacks
        for (auto& cb : oncollisionStayCallbacks) {
            if (other->hasComponent(Collider::id)) {
                cb(this, other->getComponent<Collider>());
            }
            else if (other->hasComponent(RigidBody::id)) {
                cb(this, other->getComponent<RigidBody>());
            }
		}
	}
}

void Collider::checkCollisionEnd() {
    std::list<Entity*> toDelete;
    //Limpiamos de entidades nulas antes de comprobar.
    collidedEntities.remove_if([](Entity* e) { return e->getNumberOfComponents() == 0; });
    for (auto& otherEntity : collidedEntities) {
        if (otherEntity != nullptr) {
            btRigidBody* otherBody = nullptr;
            Collider* otherCollider = nullptr;

            if (otherEntity->hasComponent<RigidBody>()) {
                otherCollider = otherEntity->getComponent<RigidBody>();
            }
            else if (otherEntity->hasComponent<Collider>()) {
                otherCollider = otherEntity->getComponent<Collider>();
            }
            //Si no tiene ningun componente de colision, algo va MUY MAL
            otherBody = otherCollider->getBody();

            if (!physicsManager->checkContact(myBody, otherBody)) {
                for (auto& cb : oncollisionLeaveCallbacks) {
                    cb(this, otherCollider);
                }
                toDelete.push_back(otherEntity);
            }
        }
        else {
	        toDelete.push_back(otherEntity);
        }
	}
    for (auto& otherEntity : toDelete) {
        if (otherEntity->getNumberOfComponents() > 0) {
			collidedEntities.remove(otherEntity);
		}
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
