#include "Transform.h"
#include "Serializer.h"
using namespace forge;

void Transform::setParent(Transform* newParent) {
	parent = newParent;
}

Transform::Transform() : 
	position(),
	rotation(),
	scale(),
	parent(nullptr) {
	serializer(position, "position");
	serializer(rotation, "rotation");
	serializer(scale, "scale");
}

void Transform::setRotation(forge::Quaternion const& newRot) {
	rotation = newRot;
}

void Transform::setRotation(forge::Vector3 const& newRot) {
	rotation = Quaternion(newRot);
}

void Transform::rotateX(float xRot) {
	rotation *= Quaternion(1, 0, 0, xRot);
}

void Transform::rotateY(float yRot) {
	rotation *= Quaternion(0, 1, 0, yRot);
}

void Transform::rotateZ(float zRot) {
	rotation *= Quaternion(0, 0, 1, zRot);
}

void Transform::setPosition(forge::Vector3 const& newPos) {
	position = newPos;
}

void Transform::movePosition(forge::Vector3 const& offset) {
	position += offset;
}

void Transform::setPositionX(float newX) {
	position.setX(newX);
}

void Transform::setPositionY(float newY) {
	position.setY(newY);
}

void Transform::setPositionZ(float newZ) {
	position.setZ(newZ);
}

void Transform::setScale(forge::Vector3 const& newScale) {
	scale = newScale;
}

void Transform::setScale(float newScale) {
	scale = Vector3(newScale);
}

void Transform::doScale(forge::Vector3 const& rescale) {
	scale *= rescale;
}

void Transform::doScale(float rescale) {
	scale *= rescale;
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