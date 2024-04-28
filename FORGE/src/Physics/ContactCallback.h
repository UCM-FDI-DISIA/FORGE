#pragma once
#include "btBulletDynamicsCommon.h"

class btCollisionWorld::ContactResultCallback;

class ContactCallback : public btCollisionWorld::ContactResultCallback{
public:
    bool m_contacting;

    ContactCallback() : m_contacting(false) {}

    btScalar addSingleResult(btManifoldPoint& cp, const btCollisionObjectWrapper* colObj0Wrap, int partId0, int index0, const btCollisionObjectWrapper* colObj1Wrap, int partId1, int index1);

};
