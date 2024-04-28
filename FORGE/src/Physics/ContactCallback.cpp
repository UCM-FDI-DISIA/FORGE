#include "ContactCallback.h"

btScalar ContactCallback::addSingleResult(btManifoldPoint& cp,const btCollisionObjectWrapper* colObj0Wrap, int partId0, int index0, const btCollisionObjectWrapper* colObj1Wrap, int partId1, int index1) {
    m_contacting = true;
    return 0;   
}
