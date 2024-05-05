#include "DebugMode.h"
#include "RenderManager.h"
#pragma warning(push)
#pragma warning(disable : 26495)
#include <LinearMath/btIDebugDraw.h>
#pragma warning(pop)

using namespace Ogre;

DebugMode::DebugMode(SceneManager* scm) {
    mContactPoints = &mContactPoints1;
    mLines = RenderManager::GetInstance()->createManualObject("physics lines");
    assert(mLines);
    mTriangles = RenderManager::GetInstance()->createManualObject("physics triangles");
    assert(mTriangles);
    mLines->setDynamic(true);
    mTriangles->setDynamic(true);

    static const char* matName = "OgreBulletCollisionsDebugDefault";
    MaterialPtr mtl = MaterialManager::getSingleton().getDefaultSettings()->clone(matName);
    mtl->setReceiveShadows(false);
    mtl->setSceneBlending(SBT_TRANSPARENT_ALPHA);
    mtl->setDepthBias(0.1, 0);
    TextureUnitState* tu = mtl->getTechnique(0)->getPass(0)->createTextureUnitState();
    assert(tu);
    tu->setColourOperationEx(LBX_SOURCE1, LBS_DIFFUSE);
    mtl->getTechnique(0)->setLightingEnabled(false);
    //mtl->getTechnique(0)->setSelfIllumination( ColourValue::White ); 

    mLines->begin(matName, RenderOperation::OT_LINE_LIST);
    mLines->position(Vector3::ZERO);
    mLines->colour(ColourValue::Blue);
    mLines->position(Vector3::ZERO);
    mLines->colour(ColourValue::Blue);

    mTriangles->begin(matName, RenderOperation::OT_TRIANGLE_LIST);
    mTriangles->position(Vector3::ZERO);
    mTriangles->colour(ColourValue::Blue);
    mTriangles->position(Vector3::ZERO);
    mTriangles->colour(ColourValue::Blue);
    mTriangles->position(Vector3::ZERO);
    mTriangles->colour(ColourValue::Blue);

    mDebugModes = (DebugDrawModes)DBG_DrawWireframe;
    Root::getSingleton().addFrameListener(this);
}

DebugMode::~DebugMode() {
}

void DebugMode::drawLine(const btVector3& from, const btVector3& to, const btVector3& color) {
    ColourValue c(color.getX(), color.getY(), color.getZ());
    c.saturate();
    mLines->position(Ogre::Vector3(from.x(), from.y(), from.z()));
    mLines->colour(c);
    mLines->position(Ogre::Vector3(to.x(), to.y(), to.z()));
    mLines->colour(c);
}

void DebugMode::drawTriangle(const btVector3& v0, const btVector3& v1, const btVector3& v2, const btVector3& color, btScalar alpha) {
    ColourValue c(color.getX(), color.getY(), color.getZ(), alpha);
    c.saturate();
    mTriangles->position(Ogre::Vector3(v0.x(), v0.y(), v0.z()));
    mTriangles->colour(c);
    mTriangles->position(Ogre::Vector3(v1.x(), v1.y(), v1.z()));
    mTriangles->colour(c);
    mTriangles->position(Ogre::Vector3(v2.x(), v2.y(), v2.z()));
    mTriangles->colour(c);
}

void DebugMode::drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color) {
    mContactPoints->resize(mContactPoints->size() + 1);
    ContactPoint p = mContactPoints->back();
    p.from = Ogre::Vector3(PointOnB.x(), PointOnB.y(), PointOnB.z());
    p.to = p.from + Ogre::Vector3(normalOnB.x(), normalOnB.y(), normalOnB.z()) * distance;
    p.dieTime = Root::getSingleton().getTimer()->getMilliseconds() + lifeTime;
    p.color.r = color.x();
    p.color.g = color.y();
    p.color.b = color.z();
}

bool DebugMode::frameStarted(const Ogre::FrameEvent& evt) {
    size_t now = Root::getSingleton().getTimer()->getMilliseconds();
    std::vector< ContactPoint >* newCP = mContactPoints == &mContactPoints1 ? &mContactPoints2 : &mContactPoints1;
    for (std::vector< ContactPoint >::iterator i = mContactPoints->begin(); i < mContactPoints->end(); i++) {
        ContactPoint& cp = *i;
        mLines->position(cp.from);
        mLines->colour(cp.color);
        mLines->position(cp.to);
        if (now <= cp.dieTime)
            newCP->push_back(cp);
    }
    mContactPoints->clear();
    mContactPoints = newCP;

    mLines->end();
    mTriangles->end();

    return true;
}

bool DebugMode::frameEnded(const Ogre::FrameEvent& evt) {
    mLines->beginUpdate(0);
    mTriangles->beginUpdate(0);
    return true;
}

void DebugMode::reportErrorWarning(const char* warningString) {
    LogManager::getSingleton().getDefaultLog()->logMessage(warningString);
}

void DebugMode::draw3dText(const btVector3& location, const char* textString) {

}

void DebugMode::setDebugMode(int debugMode) {
    mDebugModes = (DebugDrawModes)debugMode;
}

int DebugMode::getDebugMode() const {
    return mDebugModes;
}