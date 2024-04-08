#pragma once
#ifndef COLLIDER_H_
#define COLLIDER_H_
#include <Component.h>
#include <string>
#include<Vector3.h>

class PhysicsManager;
class btRigidBody;
class btCollisionShape;

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
public:
    static const std::string id;

	Collider();

	~Collider();

    bool initComponent(ComponentData* data) override;

    virtual void fixedUpdate();

    /// <summary>
    /// Metodo para comprobar si han colisionado dos colliders
    /// </summary>
    /// <param name="other: ">EL otro RigidBody con el que colisiona</param>
    /// <returns>Devuelve true si ha colisionado con otro RigidBody, false en el caso contrario</returns>
    bool hasCollidedWith(Collider* other);


    /// <summary>
    /// Registra un nuevo callback de colision
    /// </summary>
    void registerCallback(CollisionCallback callback);

    /// <summary>
    /// Maneja las colisiones con otras entidades
    /// </summary>
    /// <param name="other"></param>
    void onCollision(Entity* other);
#pragma region setters
    /// <summary>
    /// Activa y desactiva la funcion de trigger
    /// </summary>
    /// <param name="isTrigger">True si el cuerpo pasara a ser un trigger</param>
    void setTrigger(bool isTrigger);
#pragma endregion

#pragma region getters
    /// <summary>
    /// Devuelve true si es un objeto que detecta colisiones pero no choca
    /// </summary>
    bool isTrigger();

    btRigidBody* getBody();
#pragma endregion
};
#endif // !COLLIDER_H_