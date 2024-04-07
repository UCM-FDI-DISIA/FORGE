#pragma once
#ifndef RIGIDBODY_H_
#define RIGIDBODY_H_
#include <Component.h>
#include <string>
#include<Vector3.h>

class PhysicsManager;
class btRigidBody;
class btCollisionShape;

enum collisionShape
{
    ballShape, boxShape , capsuleShape, cilinderShape, planeShape
};
namespace forge {
    class Vector3;
    
};

class RigidBody : public Component {

    using CollisionCallback = void(*)(RigidBody* self, RigidBody* other); // Cualquier función que implique dos cuerpos
private:
    PhysicsManager* physicsManager;
    float mass;
    float friction;
    float restitution;
    bool kinematic;
    bool staticBody;
    bool trigger;
    btRigidBody* myBody;
    btCollisionShape* myShape;
    collisionShape shapeType;
    forge::Vector3 myScale;
    std::vector<CollisionCallback> collisionCallbacks;

    btRigidBody* getBody();

    
public:
    static const std::string id;

    RigidBody();

    ~RigidBody();

    bool initComponent(ComponentData* data) override;

    virtual void fixedUpdate();

    void applyForce(forge::Vector3 force);

    void applyGravity();

    void clearForces();

    bool hasCollidedWith(RigidBody* other);

    /// <summary>
    /// Registra un nuevo callback de colision
    /// </summary>
    void registerCallback(CollisionCallback callback);

    /// <summary>
    /// Maneja las colisiones con otros cuerpos rigidos
    /// </summary>
    /// <param name="other"></param>
    void onCollision(Entity* other);
    #pragma region setters
    /// <summary>
   /// Cambia la friccion del objeto
   /// </summary>
    void setFriction(float newFriction);

    /// <summary>
   /// Cambia la constante de restitucion
   /// </summary>
    void setRestitution(float newRestitution);

    /// <summary>
    /// Actualiza el tamaño del cuerpo para cubos y cilindros
    /// </summary>
    /// <param name="scale">Tamaño nuevo en x,y,z para el cuerpo</param>
    void setRigidScale(forge::Vector3 scale);

    /// <summary>
    /// Actualiza el tamaño del cuerpo para esferas
    /// </summary>
    /// <param name="radius">Radio nuevo para la bola</param>
    void setRigidScale(float radius);

    /// <summary>
   /// Actualiza el tamaño del cuerpo para capsulas
   /// </summary>
   /// <param name="radius">Radio nuevo para la circunferencia de la capsula</param>
   /// <param name="height">Altura nueva par ala capsula</param>
    void setRigidScale(float radius, float height);

    /// <summary>
   /// Activa y desactiva la funcion de trigger
   /// </summary>
   /// <param name="isTrigger">True si el cuerpo pasara a ser un trigger</param>
    void setTrigger(bool isTrigger);
    #pragma endregion

    #pragma region setters
    /// <summary>
  /// Devuelve la masa del objeto
  /// </summary>
    float getMass();

    /// <summary>
  /// Devuelve la friccion del objeto
  /// </summary>
    float getFriction();

    /// <summary>
  /// Devuelve la constante de restitución del objeto
  /// </summary>
    float getRestitution();

    /// <summary>
    /// Devuelve el cuerpo rigido de Bullet del objeto
    /// </summary>
    /// <returns>El btRigidbody asociado al objeto</returns>
    btRigidBody* getRigidBody();

    /// <summary>
  /// Devuelve true si es un objeto estatico
  /// </summary>
    bool isStatic();

    /// <summary>
  /// Devuelve true si es un objeto que detecta colisiones pero no choca
  /// </summary>
    bool isTrigger();

    /// <summary>
    /// Devuelve el shape del objeto
    /// </summary>
    /// <returns>la figura de colision del objeto</returns>
    btCollisionShape* getShape();

    /// <summary>
    /// Devuelve la escala del cuerpo rigido
    /// </summary>
    /// <returns>un Vector3 de FORGE con la escala del rigidbody</returns>
    forge::Vector3 getRigidScale();

    #pragma endregion
};

#endif // !RIGIDBODY_H_

