#pragma once
#ifndef CAMERA_H_
#define CAMERA_H_
#include <Component.h>
#include <string>
#include <OgreColourValue.h>
#include "Vector3.h"

class RenderManager;
namespace Ogre {
    class Camera;
}

class Camera : public Component {
private:
    std::string name;
    float nearClipDistance;
    bool autoAspectRatio;
    forge::Vector3 backgroundColor;

    Ogre::Camera* ogreCamera;
    RenderManager* renderManager; 
public:
	static const std::string id;

    Camera();
    
    ~Camera();

    bool initComponent(ComponentData* data) override;

	#pragma region setters
    void setNearClipDistance(float newNearClipDistance);
    void setAutoAspectRatio(bool newAutoAspectRatio);
    void setBackgroundColor(forge::Vector3 newbackgroundColor);
	#pragma endregion

	#pragma region getters
    const std::string& getName() const;
    const float& getNearClipDistance() const;
    const bool& getAutoAspectRatio() const;
    const forge::Vector3& getBackgroundColor() const;
	#pragma endregion
};

#endif // !CAMERA_H_