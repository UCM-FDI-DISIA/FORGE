#include "Camera.h"
#include "RenderManager.h"
#include "Entity.h"
#include "Serializer.h"
#include "OgreCamera.h"
#include "OgreColourValue.h"
#include "OgreViewport.h"

const std::string Camera::id = "Camera";

Camera::Camera() :
    ogreCamera(nullptr),
    renderManager(nullptr) {
    serializer(nearClipDistance, "nearClipDistance");
    serializer(autoAspectRatio, "autoAspectRatio");
    serializer(backgroundColor, "backgroundColor");
}

Camera::~Camera() {
   renderManager->removeNode(ogreCamera);
}

bool Camera::initComponent(ComponentData* data) {
    if(entity->hasComponent("Transform")) {
        renderManager = RenderManager::getInstance();
        try {
			ogreCamera = renderManager->addCameraNode(this);
            return ogreCamera != nullptr;
        } catch (std::exception e) {
			std::cerr << "ERROR: No se ha podido cargar la camara \n";  
            return false;
		}
    }
}

void Camera::setEnabled(bool newActive) {
    Component::setEnabled(newActive);
    if (newActive) {
        ogreCamera = renderManager->addCameraNode(this);
    }
    else {
        renderManager->removeCamera(ogreCamera);
        ogreCamera = nullptr;
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

const float& Camera::getNearClipDistance() const {
    return nearClipDistance;
}

const bool& Camera::getAutoAspectRatio() const {
    return autoAspectRatio;
}

const forge::Vector3& Camera::getBackgroundColor() const {
    return backgroundColor;
}
