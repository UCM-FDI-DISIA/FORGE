#pragma once
#ifndef COLLIDER_H_
#define COLLIDER_H_
#include <Component.h>
#include <string>
#include<Vector3.h>
#include <Quaternion.h>

class PhysicsManager;
class btRigidBody;
class btCollisionShape;
class Transform;

class Collider: public Component {
    
protected:
    enum collisionShape {
        ballShape, boxShape, capsuleShape, cilinderShape, planeShape
    };

    // Cualquier función que implique dos cuerpos
    using CollisionCallback = void(*)(Collider* self, Collider* other);

    PhysicsManager* physicsManager;
    bool trigger;
    btRigidBody* myBody;
    btCollisionShape* myShape;
    collisionShape shapeType;
    forge::Vector3 myScale;
    std::vector<CollisionCallback> collisionCallbacks;
    Transform* bodyTransform;
    std::string myShapeString;
    forge::Vector3 lastPosition;
    forge::Vector3 lastForce;
    forge::Quaternion lastOrientation;
    std::string collisionLayer;
public:
    static const FORGE_API_VAR std::string id;

    FORGE_API Collider();

    FORGE_API ~Collider();

    FORGE_API bool initComponent(ComponentData* data) override;

    virtual FORGE_API void createRigidBody(std::string myShapeType);

    virtual FORGE_API void fixedUpdate();

    virtual FORGE_API void onEnabled();

    virtual FORGE_API void onDisabled();

    /// <summary>
    /// Metodo para comprobar si han colisionado dos colliders
    /// </summary>
    /// <param name="other: ">EL otro RigidBody con el que colisiona</param>
    /// <returns>Devuelve true si ha colisionado con otro RigidBody, false en el caso contrario</returns>
    FORGE_API bool hasCollidedWith(Collider* other);

    /// <summary>
    /// Registra un nuevo callback de colision
    /// </summary>
    FORGE_API void registerCallback(CollisionCallback callback);

    /// <summary>
    /// Maneja las colisiones con otras entidades
    /// </summary>
    /// <param name="other"></param>
    FORGE_API void onCollision(Entity* other);
#pragma region setters
    /// <summary>
    /// Activa y desactiva la funcion de trigger
    /// </summary>
    /// <param name="isTrigger">True si el cuerpo pasara a ser un trigger</param>
    FORGE_API void setTrigger(bool isTrigger);
#pragma endregion

#pragma region getters
    /// <summary>
    /// Devuelve true si es un objeto que detecta colisiones pero no choca
    /// </summary>
    FORGE_API bool isTrigger();

    FORGE_API btRigidBody* getBody();

    FORGE_API std::string getLayer();
#pragma endregion
};
#endif // !COLLIDER_H_