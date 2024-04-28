#pragma once
#include "btBulletDynamicsCommon.h"

class btCollisionWorld::ContactResultCallback;

class ContactCallback : public btCollisionWorld::ContactResultCallback{
public:
    bool isContacting;

    ContactCallback() : isContacting(false) {}

    btScalar addSingleResult(btManifoldPoint& cp, const btCollisionObjectWrapper* colObj0Wrap, int partId0, int index0, const btCollisionObjectWrapper* colObj1Wrap, int partId1, int index1);

};
