#include "test.h"

testFisico::testFisico() {
	//1
	_broadphase = new btDbvtBroadphase();
	//2
	_collisionConfiguration = new btDefaultCollisionConfiguration();
	_dispatcher = new btCollisionDispatcher(_collisionConfiguration);
	//3
	_solver = new btSequentialImpulseConstraintSolver();
	//4
	_world = new btDiscreteDynamicsWorld(_dispatcher, _broadphase, _solver, _collisionConfiguration);
	//5
	_world->setGravity(btVector3((btScalar)0, (btScalar)-9.8, (btScalar)0));
}