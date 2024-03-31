#include "Transform.h"
#include "Serializer.h"
using namespace forge;

#define PI 3.14159265358979323846264338327950288

void Transform::setParent(Transform* newParent) {
	parent = newParent;
}

const std::string Transform::id = "Transform";

Transform::Transform() : 
	position(),
	rotation(),
	scale(1,1,1),
	parent(nullptr),
	needsUpdate(true) {
	serializer(position, "position");
	serializer(rotation, "rotation");
	serializer(scale, "scale");
}

void Transform::setRotation(forge::Quaternion const& newRot) {
	rotation = newRot;
	needsUpdate = true;
}

void Transform::setRotation(forge::Vector3 const& newRot) {
	rotation = Quaternion(newRot);
	needsUpdate = true;
}

void Transform::rotateX(float xRot) {
	float rad = xRot * (float)PI / 180;
	rotateXRad(rad);
}

void Transform::rotateY(float yRot) {
	float rad = yRot * (float)PI / 180;
	rotateYRad(rad);
}

void Transform::rotateZ(float zRot) {
	float rad = zRot * (float)PI / 180;
	rotateZRad(rad);
}

void Transform::rotateXRad(float xRot) {
	rotation *= Quaternion(1, 0, 0, xRot);
	needsUpdate = true;
}

void Transform::rotateYRad(float yRot) {
	rotation *= Quaternion(0, 1, 0, yRot);
	needsUpdate = true;
}

void Transform::rotateZRad(float zRot) {
	rotation *= Quaternion(0, 0, 1, zRot);
	needsUpdate = true;
}

void Transform::setPosition(forge::Vector3 const& newPos) {
	position = newPos;
	needsUpdate = true;
}

void Transform::movePosition(forge::Vector3 const& offset) {
	position += offset;
	needsUpdate = true;
}

void Transform::setPositionX(float newX) {
	position.setX(newX);
	needsUpdate = true;
}

void Transform::setPositionY(float newY) {
	position.setY(newY);
	needsUpdate = true;
}

void Transform::setPositionZ(float newZ) {
	position.setZ(newZ);
	needsUpdate = true;
}

void Transform::setScale(forge::Vector3 const& newScale) {
	scale = newScale;
	needsUpdate = true;
}

void Transform::setScale(float newScale) {
	scale = Vector3(newScale);
	needsUpdate = true;
}

void Transform::doScale(forge::Vector3 const& rescale) {
	scale *= rescale;
	needsUpdate = true;
}

void Transform::doScale(float rescale) {
	scale *= rescale;
	needsUpdate = true;
}

void Transform::setNeedsUpdate(bool needed) {
	needsUpdate = needed;
}


forge::Quaternion const& Transform::getRotation() const {
	return rotation;
}

forge::Quaternion Transform::getGlobalRotation() const {
	if (parent != nullptr) {
		return rotation * parent->getGlobalRotation();
	}
	else {
		return rotation;
	}
}

forge::Vector3 const&& Transform::getRotationEuler() const {
	return rotation.toEuler();
}

forge::Vector3 const&& Transform::getGlobalRotationEuler() const {
	return getGlobalRotation().toEuler();
}

forge::Vector3 const& Transform::getPosition() const {
	return position;
}

forge::Vector3 Transform::getGlobalPosition() const {
	if (parent != nullptr) {
		return parent->getGlobalRotation()*(position * parent->getGlobalScale()) + parent->getGlobalPosition(); 
	}
	else {
		return position;
	}
}

forge::Vector3 const& Transform::getScale() const {
	return scale;
}

forge::Vector3 Transform::getGlobalScale() const {
	if (parent != nullptr) {
		return scale * parent->getGlobalScale();
	}
	else {
		return scale;
	}
}

bool Transform::getNeedsUpdate() const {
	return needsUpdate || (parent && parent->getNeedsUpdate());
}
