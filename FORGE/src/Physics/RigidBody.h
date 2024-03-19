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
private:
    PhysicsManager* physicsManager;
    float mass;
    float friction;
    float restitution;
    bool kinematic;
    bool staticBody;
    btRigidBody* myBody;
    btCollisionShape* myShape;
    collisionShape shapeType;
    forge::Vector3 myScale;

    btRigidBody* getBody();
public:
    static const std::string id;

    RigidBody();

    ~RigidBody();

    void initComponent(ComponentData* data) override;

    virtual void fixedUpdate();

    void applyForce(forge::Vector3 force);

    void applyGravity();

    void clearForces();

    bool hasCollidedWith(RigidBody* other);
    #pragma region setters
    void setFriction(float newFriction);

    void setRestitution(float newRestitution);

    void setRigidBody(btRigidBody* body);

    void setRigidScale(forge::Vector3 scale);

    void setRigidScale(float radius);
    #pragma endregion

    #pragma region setters
    float getMass();

    float getFriction();

    float getRestitution();

    bool isStatic();

    btCollisionShape* getShape();

    forge::Vector3 getRigidScale();

    #pragma endregion
};

#endif // !RIGIDBODY_H_

