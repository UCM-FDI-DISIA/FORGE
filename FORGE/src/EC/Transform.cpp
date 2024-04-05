#include "Transform.h"
#include "Serializer.h"
using namespace forge;

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
	rotation *= Quaternion(1, 0, 0, xRot);
	needsUpdate = true;
}

void Transform::rotateY(float yRot) {
	rotation *= Quaternion(0, 1, 0, yRot);
	needsUpdate = true;
}

void Transform::rotateZ(float zRot) {
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

forge::Vector3 Transform::getRotationEuler() const {
	return rotation.toEuler();
}

forge::Vector3 Transform::getGlobalRotationEuler() const {
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

forge::Vector3 Transform::getForward() const {
	return getGlobalRotation() * Vector3::FORWARD;
}

forge::Vector3 Transform::getUp() const {
	return getGlobalRotation() * Vector3::UP;
}

forge::Vector3 Transform::getRight() const {
	return getGlobalRotation() * Vector3::RIGHT;
}