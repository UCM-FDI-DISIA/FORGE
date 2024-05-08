#ifdef _DEBUG
#ifndef DEBUG_MODE_H_
#define DEBUG_MODE_H_
#include <vector>
#pragma warning(push)
#pragma warning(disable : 4244)
#pragma warning(disable : 4251)
#pragma warning(disable : 26439)
#pragma warning(disable : 26451)
#pragma warning(disable : 26495)
#include <Ogre.h>
#pragma warning(pop)
#pragma warning(push)
#pragma warning(disable : 26495)
#include <btBulletCollisionCommon.h>
#pragma warning(pop)

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
    Ogre::Root& ogreRoot;
    std::vector<ContactPoint>& mContactPoints;
    std::vector<ContactPoint>& otherContactPoints;
    std::vector<ContactPoint>  mContactPoints1;
    std::vector<ContactPoint>  mContactPoints2;

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
    bool init();
    /// <summary>
    /// Método para dibujar las lineas de los cuerpos fisicos
    /// </summary>
    void drawLine(const btVector3& from, const btVector3& to, const btVector3& color) override;
    /// <summary>
    /// Método para dibujar triangulos de los cuerpos fisicos (actualmente no se usa)
    /// </summary>
    void drawTriangle(const btVector3& v0, const btVector3& v1, const btVector3& v2, const btVector3& color, btScalar) override;
    /// <summary>
    /// Método para representar los puntos de choque de dos cuerpos fisicos
    /// </summary>
    void drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color) override;
    /// <summary>
    /// Escribe un error o warning producido durante el debug
    /// </summary>
    /// <param name="warningString"> Error a reportar</param>
    void reportErrorWarning(const char* warningString) override;
    /// <summary>
    /// Dibuja texto en 3d para informar
    /// </summary>
    /// <param name="location"> Posicion donde dibujarlo</param>
    /// <param name="textString"> Texto a dibujar</param>
    void draw3dText(const btVector3& location, const char* textString) override;
    /// <summary>
    /// Setea las flags para señalar que dibujar, como puntos de colision, cuerpos,etc..
    /// </summary>
    /// <param name="debugMode"> Flags para indicar que dibujar</param>
    void setDebugMode(int debugMode) override;
    /// <summary>
    /// Devuelve las flags que se han aplicado
    /// </summary>
    /// <returns> Un entero con las flags</returns>
    int getDebugMode() const override;
};
#endif // _DEBUG
#endif // !DEBUG_MODE_H_