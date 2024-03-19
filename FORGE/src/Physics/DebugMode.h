#include "LinearMath/btIDebugDraw.h"
#include "SDL_opengl.h"

class DebugMode : public btIDebugDraw
{
	int myDebugMode;

public:

	DebugMode() {};
	virtual ~DebugMode();

	virtual void drawLine(const btVector3& from, const btVector3& to, const btVector3& color) {
            glPushMatrix();
            glColor4f(color.getX(), color.getY(), color.getZ(), 1.0);

            const GLfloat line[] = {
                from.getX() * 1, from.getY() * 1, from.getZ() * 1, //point A
                to.getX() * 1, to.getY() * 1,to.getZ() * 1 //point B
            };
            glVertexPointer(3,
                            GL_FLOAT,
                            0,
                            &line);
            glPointSize(5.0f);
            glDrawArrays(GL_POINTS, 0, 2);
            glDrawArrays(GL_LINES, 0, 2);
            glPopMatrix();
    }
    virtual void drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color) {};

    virtual void reportErrorWarning(const char* warningString) {};

    virtual void draw3dText(const btVector3& location, const char* textString) {};

    virtual void setDebugMode(int debugMode) {};

	virtual int getDebugMode() const { return myDebugMode; }

};