#pragma once
#include <btBulletDynamicsCommon.h>
class testFisico {
private:
    btBroadphaseInterface* _broadphase;
    btDefaultCollisionConfiguration* _collisionConfiguration;
    btCollisionDispatcher* _dispatcher;
    btSequentialImpulseConstraintSolver* _solver;
    btDiscreteDynamicsWorld* _world;
    btRigidBody* _myBody;
    btCollisionShape* _shape;
public:
    testFisico();
};