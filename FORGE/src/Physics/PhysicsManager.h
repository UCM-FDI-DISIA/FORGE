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
    std::unordered_map<std::string, btRigidBody*> importantObjects;

    /// <summary>
    /// Constructora del physics manager.
    /// </summary>
    PhysicsManager();

public:
    
    /// <summary>
    /// Inicializa el mundo de fisicas y pone una gravedad default (9.8)
    /// </summary>
    void initPhysics();

    /// <summary>
    /// Ordena al mundo de fisicas que actualice su estado. Avabza la simulacion 20ms, para que coincida con el tiempo de refresco de fixedUpdate
    /// </summary>
    void updatePhysics();

    /// <returns>Devuelve una instancia al PhysicsManager</returns>
    static PhysicsManager* getInstance();
    btRigidBody* createBody(RigidBody* body);
    btRigidBody* createImportantBody(RigidBody* body, std::string name);
    void deleteBody(btRigidBody* body);
};

