#pragma once
#ifndef RIGIDBODY_H_
#define RIGIDBODY_H_
#include <Component.h>
#include <string>

class PhysicsManager;
class btRigidBody;
class btCollisionShape;

class RigidBody : public Component {
private:
    PhysicsManager* physicsManager;
    float mass;
    float friction;
    float restitution;
    bool kinematic;
    btRigidBody* myBody;
    btCollisionShape* myShape;
public:
    static const std::string id;

    RigidBody();

    ~RigidBody();

    void initComponent(ComponentData* data) override;

    virtual void fixedUpdate();

    void applyForce(forge::Vector3 force);

    void applyGravity();

    void clearForces();
    #pragma region setters
    void setFriction(float newFriction);

    void setRestitution(float newRestitution);
    #pragma endregion

    #pragma region setters
    float getMass();

    float getFriction();

    float getRestitution();

    btCollisionShape* getShape();
    #pragma endregion
};

#endif // !RIGIDBODY_H_

