#pragma once
#pragma warning(push)
#pragma warning(disable : 26495)
#include <btBulletDynamicsCommon.h>
#pragma warning(pop)

class ContactCallback : public btCollisionWorld::ContactResultCallback {
private:
    bool isContacting;

public:

    ContactCallback();

    btScalar addSingleResult(btManifoldPoint& cp, const btCollisionObjectWrapper* colObj0Wrap, int partId0, int index0, const btCollisionObjectWrapper* colObj1Wrap, int partId1, int index1);

    bool contacting() const;
};
