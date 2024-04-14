#ifndef DebugDrawer_h__
#define DebugDrawer_h__
#include <vector>
#include <Ogre.h>
#include <btBulletCollisionCommon.h>
#include "ForgeExport.h"

/// <summary>
/// Struct para guardar los puntos de cintacto entre bodies
/// </summary>
struct ContactPoint {
    Ogre::Vector3 from;
    Ogre::Vector3 to;
    Ogre::ColourValue color;
    size_t dieTime;
};

class DebugMode : public btIDebugDraw, public Ogre::FrameListener {
private:

    DebugDrawModes mDebugModes;
    Ogre::ManualObject* mLines;
    Ogre::ManualObject* mTriangles;
    std::vector< ContactPoint >* mContactPoints;
    std::vector< ContactPoint >  mContactPoints1;
    std::vector< ContactPoint >  mContactPoints2;
protected:
    /// <summary>
    /// Método heredado de frame renderer para escuchar eventos
    /// </summary>
    bool frameStarted(const Ogre::FrameEvent& evt);
    /// <summary>
    /// Método heredado de frame renderer para escuchar eventos
    /// </summary>
    bool frameEnded(const Ogre::FrameEvent& evt);
public:
    FORGE_API DebugMode(Ogre::SceneManager* scm);
    FORGE_API ~DebugMode();
    /// <summary>
    /// Método para dibujar las lineas de los cuerpos fisicos
    /// </summary>
    virtual FORGE_API void drawLine(const btVector3& from, const btVector3& to, const btVector3& color);
    /// <summary>
    /// Método para dibujar triangulos de los cuerpos fisicos (actualmente no se usa)
    /// </summary>
    virtual FORGE_API void drawTriangle(const btVector3& v0, const btVector3& v1, const btVector3& v2, const btVector3& color, btScalar);
    /// <summary>
    /// Método para representar los puntos de choque de dos cuerpos fisicos
    /// </summary>
    virtual FORGE_API void drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color);
    virtual FORGE_API void reportErrorWarning(const char* warningString);
    virtual FORGE_API void draw3dText(const btVector3& location, const char* textString);
    virtual FORGE_API void setDebugMode(int debugMode);
    virtual FORGE_API int getDebugMode() const;
};

#endif // DebugDrawer_h__