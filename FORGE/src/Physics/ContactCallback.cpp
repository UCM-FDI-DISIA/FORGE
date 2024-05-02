#include "ContactCallback.h"

ContactCallback::ContactCallback() : 
    isContacting(false) {
}

btScalar ContactCallback::addSingleResult(btManifoldPoint& cp,const btCollisionObjectWrapper* colObj0Wrap, int partId0, int index0, const btCollisionObjectWrapper* colObj1Wrap, int partId1, int index1) {
    isContacting = true;
    return 0;   
}

bool ContactCallback::contacting() const {
    return isContacting;
}
