#pragma once
#ifndef RIGIDBODY_H_
#define RIGIDBODY_H_
#include <string>
#include "Component.h"
#include "Vector3.h"
#include "Collider.h"

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
    std::vector<bool> axisBlockedPos;
    std::vector<bool> axisBlockedRot;

public:
    static const FORGE_API_VAR std::string id;

    FORGE_API RigidBody();

    FORGE_API bool initComponent(ComponentData* data) override;

    virtual FORGE_API void createRigidBody(std::string myShapeType);

    /// <summary>
    /// Metodo para aplicar fuerzas a un rigidbody
    /// </summary>
    /// <param name="force: ">Fuerza en vector 3 a aplicar al objeto</param>
    FORGE_API void applyForce(forge::Vector3 force);

    /// <summary>
    /// Metodo para aplicar gravedad nueva a un objeto
    /// </summary>
    /// <param name="newGravity: ">La gravedad nueva a aplicar</param>
    FORGE_API void setGravity(forge::Vector3 newGravity);

    /// <summary>
    /// Limpia las fuerzas aplicadas al objeto, devolviendolo a un estado sin fuerzas aplicadas
    /// </summary>
    FORGE_API void clearForces();

    #pragma region setters

    /// <summary>
    /// Añade bloqueos para evitar movimiento en los ejes
    /// </summary>
    /// <param name="x :">True significa bloqueo en el eje</param>
    /// <param name="y :">True significa bloqueo en el eje</param>
    /// <param name="z :">True significa bloqueo en el eje</param>
    FORGE_API void lockPosition(bool x, bool y, bool z);

    /// <summary>
    /// Añade bloqueos para evitar rotación en los ejes
    /// </summary>
    /// <param name="x :">True significa bloqueo en el eje</param>
    /// <param name="y :">True significa bloqueo en el eje</param>
    /// <param name="z :">True significa bloqueo en el eje</param>
    FORGE_API void lockRotation(bool x, bool y, bool z);

    /// <summary>
    /// Cambia la friccion del objeto
    /// </summary>
    FORGE_API void setFriction(float newFriction);

    /// <summary>
    /// Cambia la constante de restitucion
    /// </summary>
    FORGE_API void setRestitution(float newRestitution);

    /// <summary>
    /// Actualiza el tamaño del cuerpo para cubos y cilindros
    /// </summary>
    /// <param name="scale">Tamaño nuevo en x,y,z para el cuerpo</param>
    FORGE_API void setRigidScale(forge::Vector3 scale);

    /// <summary>
    /// Actualiza el tamaño del cuerpo para esferas
    /// </summary>
    /// <param name="radius">Radio nuevo para la bola</param>
    FORGE_API void setRigidScale(float radius);

    /// <summary>
    /// Actualiza el tamaño del cuerpo para capsulas
    /// </summary>
    /// <param name="radius">Radio nuevo para la circunferencia de la capsula</param>
    /// <param name="height">Altura nueva par ala capsula</param>
    FORGE_API void setRigidScale(float radius, float height);

    FORGE_API void setPositionX(float newX);
    FORGE_API void setPositionY(float newY);
    FORGE_API void setPositionZ(float newZ);
    FORGE_API void rotateX(float newAngle);
    FORGE_API void rotateY(float newAngle);
    FORGE_API void rotateZ(float newAngle);
    #pragma endregion

    #pragma region getters
    /// <summary>
    /// Devuelve la masa del objeto
    /// </summary>
    FORGE_API float getMass();

    /// <summary>
    /// Devuelve la friccion del objeto
    /// </summary>
    FORGE_API float getFriction();

    /// <summary>
    /// Devuelve la constante de restitución del objeto
    /// </summary>
    FORGE_API float getRestitution();

    /// <summary>
    /// Devuelve el cuerpo rigido de Bullet del objeto
    /// </summary>
    /// <returns>El btRigidbody asociado al objeto</returns>
    FORGE_API btRigidBody* getRigidBody();

    /// <summary>
    /// Devuelve true si es un objeto estatico
    /// </summary>
    FORGE_API bool isStatic();

    /// <summary>
    /// Devuelve el shape del objeto
    /// </summary>
    /// <returns>la figura de colision del objeto</returns>
    FORGE_API btCollisionShape* getShape();

    /// <summary>
    /// Devuelve la escala del cuerpo rigido
    /// </summary>
    /// <returns>un Vector3 de FORGE con la escala del rigidbody</returns>
    FORGE_API forge::Vector3 getRigidScale();

    /// <summary>
    /// Devuelve la velocidad (modulo de la fuerza) del cuerpo rigido
    /// </summary>
    /// <returns>un float con la velocidad</returns>
    FORGE_API float getSpeed();

    #pragma endregion
};

#endif // !RIGIDBODY_H_