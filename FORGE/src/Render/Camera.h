#pragma once
#ifndef CAMERA_H_
#define CAMERA_H_
#include "Component.h"
#include <string>
#include "Vector3.h"
#include "ForgeExport.h"

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
    static const FORGE_API_VAR std::string id;

    FORGE_API Camera();
    
    FORGE_API ~Camera();

    FORGE_API void initComponent(ComponentData* data) override;

	#pragma region setters
    FORGE_API void setNearClipDistance(float newNearClipDistance);
    FORGE_API void setAutoAspectRatio(bool newAutoAspectRatio);
    FORGE_API void setBackgroundColor(forge::Vector3 newbackgroundColor);
	#pragma endregion

	#pragma region getters
    const FORGE_API std::string& getName() const;
    const FORGE_API float& getNearClipDistance() const;
    const FORGE_API bool& getAutoAspectRatio() const;
    const FORGE_API forge::Vector3& getBackgroundColor() const;
	#pragma endregion
};

#endif // !CAMERA_H_