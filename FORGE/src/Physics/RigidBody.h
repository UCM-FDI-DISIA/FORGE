#pragma once
#ifndef RIGIDBODY_H_
#define RIGIDBODY_H_
#include <string>
#include "Collider.h"

namespace forge {
    class Vector3;
};

class RigidBody : public Collider {
protected:
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

    FORGE_API bool createRigidBody(std::string const& myShapeType, float mass, bool isStatic, bool disableDeactivation) override;

    FORGE_API void onEnabled() override;

    /// <summary>
    /// Metodo para aplicar fuerzas a un rigidbody
    /// </summary>
    /// <param name="force">Fuerza en vector 3 a aplicar al objeto</param>
    FORGE_API void applyForce(forge::Vector3 const& force);

    /// <summary>
    /// Limpia las fuerzas aplicadas al objeto, devolviendolo a un estado sin fuerzas aplicadas
    /// </summary>
    FORGE_API void clearForces();

    #pragma region setters
    /// <summary>
    /// Metodo para aplicar gravedad nueva a un objeto
    /// </summary>
    /// <param name="newGravity">La gravedad nueva a aplicar</param>
    FORGE_API void setGravity(forge::Vector3 const& newGravity);
    /// <summary>
    /// Metodo para devolver un objeto a su estado de reposo
    /// </summary>
    FORGE_API void rest();
    /// <summary>
    /// Añade bloqueos para evitar movimiento en los ejes
    /// </summary>
    /// <param name="x">True significa bloqueo en el eje</param>
    /// <param name="y">True significa bloqueo en el eje</param>
    /// <param name="z">True significa bloqueo en el eje</param>
    FORGE_API void lockPosition(bool x, bool y, bool z);
    /// <summary>
    /// Añade bloqueos para evitar rotación en los ejes
    /// </summary>
    /// <param name="x">True significa bloqueo en el eje</param>
    /// <param name="y">True significa bloqueo en el eje</param>
    /// <param name="z">True significa bloqueo en el eje</param>
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
    /// Actualiza la escala del cuerpo
    /// </summary>
    /// <param name="scale">Escala nueva en x,y,z para el cuerpo</param>
    FORGE_API void setRigidScale(forge::Vector3 const& scale);
    /// <summary>
    /// Actualiza la velocidad lineal del objeto
    /// </summary>
    /// <param name="vect">Vector 3 de forge con la velocidad a aplicar</param>
    FORGE_API void setLinearVelocity(forge::Vector3 const& vect);
    /// <summary>
    /// Actualiza la velocidad Angular del objeto
    /// </summary>
    /// <param name="vect">Vector 3 de forge con la velocidad a aplicar</param>
    FORGE_API void setAngularVelocity(forge::Vector3 const& vect);
    /// <summary>
    /// Metodo para actualizar la posicion a partir de otro vector
    /// </summary>
    /// <param name="vect">Vector 3 de forge</param>
    FORGE_API void setPosition(forge::Vector3 const& vect);
    /// <summary>
    /// Cambia la posicion en x por el nuevo valor
    /// </summary>
    /// <param name="newX">Valor de x nuevo</param>
    FORGE_API void setPositionX(float newX);

    /// <summary>
    /// Cambia la posicion en y por el nuevo valor
    /// </summary>
    /// <param name="newY">Valor de y nuevo</param>
    FORGE_API void setPositionY(float newY);

    /// <summary>
    /// Cambia la posicion en z por el nuevo valor
    /// </summary>
    /// <param name="newZ"> Valor de z nuevo</param>
    FORGE_API void setPositionZ(float newZ);

    /// <summary>
    /// Rota en el eje x el nuevo valor
    /// </summary>
    /// <param name="newAngle"> Valor a rotar en grados</param>
    FORGE_API void rotateX(float newAngle);

    /// <summary>
    /// Rota en el eje y el nuevo valor
    /// </summary>
    /// <param name="newAngle"> Valor a rotar en grados</param>
    FORGE_API void rotateY(float newAngle);

    /// <summary>
    /// Rota en el eje z el nuevo valor
    /// </summary>
    /// <param name="newAngle"> Valor a rotar en grados</param>
    FORGE_API void rotateZ(float newAngle);
    #pragma endregion

    #pragma region Getters
    /// <summary>
    /// Devuelve la masa del objeto
    /// </summary>
    FORGE_API float getMass();

    /// <summary>
    /// Devuelve la gravedad del objeto
    /// </summary>
    FORGE_API forge::Vector3 getGravity();
    /// <summary>
    /// Devuelve la friccion del objeto
    /// </summary>
    FORGE_API float getFriction();

    /// <summary>
    /// Devuelve la constante de restitución del objeto
    /// </summary>
    FORGE_API float getRestitution();

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

    /// <summary>
    /// Devuelve la velocidad lineal del cuerpo rigido
    /// </summary>
    /// <returns>un vector 3 con la velocidad</returns>
    FORGE_API forge::Vector3 getLinearVelocity();

    /// <summary>
    /// Devuelve la velocidad angular del cuerpo rigido
    /// </summary>
    /// <returns>un vector 3 con la velocidad</returns>
    FORGE_API forge::Vector3 getAngularVelocity();
    #pragma endregion
};

#endif // !RIGIDBODY_H_