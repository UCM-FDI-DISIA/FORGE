#include "Camera.h"
#include "RenderManager.h"
#include "Entity.h"
#include "Serializer.h"
#pragma warning(push)
#pragma warning(disable : 4251)
#pragma warning(disable : 26439)
#pragma warning(disable : 26451)
#pragma warning(disable : 26495)
#include <OgreCamera.h>
#include <OgreColourValue.h>
#include <OgreViewport.h>
#pragma warning(pop)

const std::string Camera::id = "Camera";


Camera::Camera() :
    ogreCamera(nullptr),
    renderManager(nullptr) {
    serializer(nearClipDistance, "nearClipDistance");
    serializer(autoAspectRatio, "autoAspectRatio");
    serializer(backgroundColor, "backgroundColor");
}

Camera::~Camera() {
   if(ogreCamera != nullptr && renderManager != nullptr)
   {
       renderManager->removeNode(ogreCamera);
   }
}

bool Camera::initComponent(ComponentData* data) {
    if(entity->hasComponent("Transform")) {
        renderManager = RenderManager::GetInstance();
		ogreCamera = renderManager->addCameraNode(this);
    }
    else {
        reportError("Se requiere un componente Transform para generar una Camera");
    }
    return ogreCamera != nullptr;
}

void Camera::onEnabled() {
    ogreCamera = renderManager->addCameraNode(this);
}

void Camera::onDisabled() {
    renderManager->removeCamera(ogreCamera);
    ogreCamera = nullptr;
}

void Camera::setNearClipDistance(float newNearClipDistance) {
    nearClipDistance = newNearClipDistance;
    ogreCamera->setNearClipDistance(nearClipDistance);

}

void Camera::setAutoAspectRatio(bool newAutoAspectRatio) {
    autoAspectRatio = newAutoAspectRatio;
    ogreCamera->setAutoAspectRatio(newAutoAspectRatio);
}

void Camera::setBackgroundColor(forge::Vector3 const& newbackgroundColor) {
    backgroundColor = newbackgroundColor;
    Ogre::ColourValue value = Ogre::ColourValue(backgroundColor.getX(), backgroundColor.getY(), backgroundColor.getZ());
    ogreCamera->getViewport()->setBackgroundColour(value);
}

const float& Camera::getNearClipDistance() const {
    return nearClipDistance;
}

const bool& Camera::getAutoAspectRatio() const {
    return autoAspectRatio;
}

const forge::Vector3& Camera::getBackgroundColor() const {
    return backgroundColor;
}
