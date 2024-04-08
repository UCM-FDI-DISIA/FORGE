#ifndef DebugDrawer_h__
#define DebugDrawer_h__
#include<Ogre.h>
#include "LinearMath/btIDebugDraw.h"

class DebugMode : public btIDebugDraw, public Ogre::FrameListener {
private:
    /// <summary>
    /// Struct para guardar los puntos de cintacto entre bodies
    /// </summary>
    struct ContactPoint {
        Ogre::Vector3 from;
        Ogre::Vector3 to;
        Ogre::ColourValue   color;
        size_t        dieTime;
    };
    DebugDrawModes               mDebugModes;
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
    DebugMode(Ogre::SceneManager* scm);
    ~DebugMode();
    /// <summary>
    /// Método para dibujar las lineas de los cuerpos fisicos
    /// </summary>
    virtual void drawLine(const btVector3& from, const btVector3& to, const btVector3& color);
    /// <summary>
    /// Método para dibujar triangulos de los cuerpos fisicos (actualmente no se usa)
    /// </summary>
    virtual void drawTriangle(const btVector3& v0, const btVector3& v1, const btVector3& v2, const btVector3& color, btScalar);
    /// <summary>
    /// Método para representar los puntos de choque de dos cuerpos fisicos
    /// </summary>
    virtual void drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color);
    virtual void reportErrorWarning(const char* warningString);
    virtual void draw3dText(const btVector3& location, const char* textString);
    virtual void setDebugMode(int debugMode);
    virtual int getDebugMode() const;
};

#endif // DebugDrawer_h__