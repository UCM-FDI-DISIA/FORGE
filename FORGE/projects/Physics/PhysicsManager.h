#pragma once
#include <btBulletDynamicsCommon.h>
#include <memory>
#include <unordered_map>


class Transform;
class RigidBody;
class PhysicsManager
{
private:
	static std::unique_ptr<PhysicsManager> instance;
    btBroadphaseInterface* broadphase;
    btDefaultCollisionConfiguration* collisionConfiguration;
    btCollisionDispatcher* dispatcher;
    btSequentialImpulseConstraintSolver* solver;
    btDiscreteDynamicsWorld* world;
    std::unordered_map<btRigidBody*, Transform*> transforms;

    /// <summary>
    /// Constructora del physics manager.
    /// </summary>
    PhysicsManager();

public:
    
    /// <summary>
    /// Inicializa el mundo de fisicas y pone una gravedad default (9.8)
    /// </summary>
    void initPhysics();

    /// <returns>Devuelve una instancia al PhysicsManager</returns>
    static PhysicsManager* getInstance();
    btRigidBody* createBody(RigidBody* body);
    void deleteBody(btRigidBody* body);
};

