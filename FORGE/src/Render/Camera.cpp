#include "Camera.h"
#include "RenderManager.h"
#include "Entity.h"
#include "Serializer.h"
#include "OgreCamera.h"
#include "OgreColourValue.h"
#include "OgreViewport.h"

const std::string Camera::id = "Mesh";

Camera::Camera() :
    ogreCamera(nullptr),
    renderManager(nullptr) {
    serializer(name, "name");
    serializer(nearClipDistance, "nearClipDistance");
    serializer(autoAspectRatio, "autoAspectRatio");
    serializer(backgroundColor, "backgroundColor");
}

Camera::~Camera() {
   renderManager->removeNode(ogreCamera);
}

void Camera::initComponent(ComponentData* data) {
    if(entity->hasComponent("Transform")) {
        renderManager = RenderManager::getInstance();
        ogreCamera = renderManager->addCameraNode(this);
    }
}

void Camera::setNearClipDistance(float newNearClipDistance) {
    nearClipDistance = newNearClipDistance;
    ogreCamera->setNearClipDistance(nearClipDistance);

}

void Camera::setAutoAspectRatio(bool newAutoAspectRatio) {
    autoAspectRatio = newAutoAspectRatio;
    ogreCamera->setAutoAspectRatio(newAutoAspectRatio);
}

void Camera::setBackgroundColor(forge::Vector3 newbackgroundColor) {
    backgroundColor = newbackgroundColor;
    Ogre::ColourValue value = Ogre::ColourValue(backgroundColor.getX(), backgroundColor.getY(), backgroundColor.getZ());
    ogreCamera->getViewport()->setBackgroundColour(value);
}

const std::string& Camera::getName() const {
    return name;
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
