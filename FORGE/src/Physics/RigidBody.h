#pragma once
#ifndef RIGIDBODY_H_
#define RIGIDBODY_H_
#include <Component.h>
#include <string>
#include<Vector3.h>
#include "Collider.h"

class PhysicsManager;
class btRigidBody;
class btCollisionShape;

enum collisionShape {
    ballShape, boxShape , capsuleShape, cilinderShape, planeShape
};
namespace forge {
    class Vector3;
};

class RigidBody : public Collider {

private:
    float mass;
    float friction;
    float restitution;
    bool kinematic;
    bool staticBody;
    forge::Vector3 myGravity;
    std::vector<bool> axisBlocked;

public:
    static const std::string id;

    RigidBody();

    bool initComponent(ComponentData* data) override;

    /// <summary>
    /// Metodo para aplicar fuerzas a un rigidbody
    /// </summary>
    /// <param name="force: ">Fuerza en vector 3 a aplicar al objeto</param>
    void applyForce(forge::Vector3 force);

    /// <summary>
    /// Metodo para aplicar gravedad nueva a un objeto
    /// </summary>
    /// <param name="newGravity: ">La gravedad nueva a aplicar</param>
    void setGravity(forge::Vector3 newGravity);

    /// <summary>
    /// Limpia las fuerzas aplicadas al objeto, devolviendolo a un estado sin fuerzas aplicadas
    /// </summary>
    void clearForces();

    #pragma region setters

    /// <summary>
    /// Añade bloqueos para evitar movimiento en los ejes
    /// </summary>
    /// <param name="x :">True significa bloqueo en el eje</param>
    /// <param name="y :">True significa bloqueo en el eje</param>
    /// <param name="z :">True significa bloqueo en el eje</param>
    void lockPosition(bool x, bool y, bool z);

    /// <summary>
    /// Añade bloqueos para evitar rotación en los ejes
    /// </summary>
    /// <param name="x :">True significa bloqueo en el eje</param>
    /// <param name="y :">True significa bloqueo en el eje</param>
    /// <param name="z :">True significa bloqueo en el eje</param>
    void lockRotation(bool x, bool y, bool z);

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
    #pragma endregion

    #pragma region getters
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