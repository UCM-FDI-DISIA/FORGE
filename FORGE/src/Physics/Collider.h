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

class Collider: public Component {
    
protected:
    enum collisionShape {
        ballShape, boxShape, capsuleShape, cilinderShape, planeShape
    };
    PhysicsManager* physicsManager;
    bool trigger;
    btRigidBody* myBody;
    btCollisionShape* myShape;
    collisionShape shapeType;
    forge::Vector3 myScale;
    std::vector<std::function<void(Collider*, Collider*)>> onCollisionEnterCallbacks;
    std::vector<std::function<void(Collider*, Collider*)>> oncollisionStayCallbacks;
    std::vector<std::function<void(Collider*, Collider*)>> oncollisionLeaveCallbacks;
    Transform* bodyTransform;
    std::string myShapeString;
    forge::Vector3 lastPosition;
    forge::Vector3 lastForce;
    forge::Quaternion lastOrientation;
    std::string collisionLayer;
    std::list<Entity*> collidedEntities;
public:
    enum callbackType {
        onCollisionEnter, onCollisionStay, onCollisionLeave
    };

    static const FORGE_API_VAR std::string id;

    FORGE_API Collider();

    FORGE_API ~Collider();

    FORGE_API bool initComponent(ComponentData* data) override;

    FORGE_API void fixedUpdate() override;

    FORGE_API void onEnabled() override;

    FORGE_API void onDisabled() override;

    FORGE_API virtual void createRigidBody(std::string const& myShapeType);

    /// <summary>
    /// Metodo para comprobar si han colisionado dos colliders
    /// </summary>
    /// <param name="other: ">EL otro RigidBody con el que colisiona</param>
    /// <returns>Devuelve true si ha colisionado con otro RigidBody, false en el caso contrario</returns>
    FORGE_API bool hasCollidedWith(Entity* other);

    /// <summary>
    /// Registra un nuevo callback de colision
    /// </summary>
    FORGE_API void registerCallback(callbackType type, std::function<void(Collider*, Collider*)> callback);

    /// <summary>
    /// Maneja las colisiones con otras entidades
    /// </summary>
    /// <param name="other"></param>
    FORGE_API void onCollision(Entity* other);

    /// <summary>
    /// Si se ha dejado de colisionar con otras entidades, se llama a los callbacks de fin de colision
    /// </summary>
    FORGE_API void checkCollisionEnd();
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

    /// <summary>
    /// Devuelve el cuerpo fisico de bullet
    /// </summary>
    /// <returns> El cuerpo fisico</returns>
    FORGE_API btRigidBody* getBody();

    /// <summary>
    /// Devuelve el nombre de la capa en la que esta el objeto
    /// </summary>
    /// <returns> La capa del objeto</returns>
    FORGE_API std::string getLayer();

    /// <summary>
    /// Devuelve la posición del cuerpo fisico
    /// </summary>
    /// <returns> La posición en forge vector</returns>
    FORGE_API forge::Vector3 getPosition();
#pragma endregion
};
#endif // !COLLIDER_H_