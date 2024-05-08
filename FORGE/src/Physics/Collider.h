#pragma once
#ifndef COLLIDER_H_
#define COLLIDER_H_
#include "Component.h"
#include <functional>
#include <list>
#include <vector>
#include "Vector3.h"
#include "Quaternion.h"

class PhysicsManager;
class btRigidBody;
class btCollisionShape;
class Transform;

namespace forge {
    enum callbackType {
        onCollisionEnter, onCollisionStay, onCollisionLeave
    };
}

class Collider: public Component {
protected:
    enum collisionShape {
        ballShape, boxShape, capsuleShape, cylinderShape, planeShape
    };

    PhysicsManager& physicsManager;
    bool trigger;
    btRigidBody* myBody;
    btCollisionShape* myShape;
    std::string myShapeString;
    collisionShape shapeType;

    Transform* bodyTransform;
    forge::Vector3 myScale;
    forge::Vector3 offset;

    forge::Vector3 lastPosition;
    forge::Vector3 lastForce;
    forge::Quaternion lastOrientation;

    std::vector<std::function<void(Collider*, Collider*)>> onCollisionEnterCallbacks;
    std::vector<std::function<void(Collider*, Collider*)>> oncollisionStayCallbacks;
    std::vector<std::function<void(Collider*, Collider*)>> oncollisionLeaveCallbacks;

    std::string collisionLayer;
    std::list<Entity*> collidedEntities;
public:
    static const FORGE_API_VAR std::string id;

    FORGE_API Collider();

    FORGE_API ~Collider();

    FORGE_API bool initComponent(ComponentData* data) override;

    FORGE_API void fixedUpdate() override;

    FORGE_API void onEnabled() override;

    FORGE_API void onDisabled() override;

    FORGE_API virtual bool createRigidBody(std::string const& myShapeType, float mass, bool isStatic, bool disableDeactivation);

    /// <summary>
    /// Metodo para comprobar si han colisionado dos colliders
    /// </summary>
    /// <param name="other">El otro RigidBody con el que colisiona</param>
    /// <returns>Devuelve true si ha colisionado con otro RigidBody, false en el caso contrario</returns>
    FORGE_API bool hasCollidedWith(Entity* other);

    /// <summary>
    /// Registra un nuevo callback de colision
    /// </summary>
    FORGE_API void registerCallback(forge::callbackType type, std::function<void(Collider*, Collider*)> callback);

    /// <summary>
    /// Maneja las colisiones con otras entidades
    /// </summary>
    /// <param name="other"></param>
    FORGE_API void onCollision(Entity* other);

    /// <summary>
    /// Si se ha dejado de colisionar con otras entidades, se llama a los callbacks de fin de colision
    /// </summary>
    FORGE_API void checkCollisionEnd();

    #pragma region Getters
    /// <returns>
    /// Devuelve true si es un objeto que detecta colisiones pero no choca
    /// </returns>
    FORGE_API bool isTrigger() const;

    /// <returns>
    /// El cuerpo fisico
    /// </returns>
    FORGE_API btRigidBody* getBody();

    /// <returns>
    /// El nombre la capa del objeto
    /// </returns>
    FORGE_API std::string getLayer() const;

    ///<returns>
    ///La posición en forge vector
    ///</returns>
    FORGE_API forge::Vector3 getPosition() const;
    #pragma endregion

    #pragma region Setters
    /// <summary>
    /// Activa y desactiva la funcion de trigger
    /// </summary>
    /// <param name="isTrigger">True si el cuerpo pasara a ser un trigger</param>
    FORGE_API void setTrigger(bool isTrigger);
    #pragma endregion
};
#endif // !COLLIDER_H_