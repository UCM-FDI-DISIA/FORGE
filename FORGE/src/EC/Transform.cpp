#include "Transform.h"
#include "Serializer.h"

Transform::Transform() : 
	position(),
	rotation(),
	scale() {
	serialize()(position, "position");
	serialize()(rotation, "rotation");
	serialize()(scale, "scale");
}

void Transform::initComponent( ComponentData* data) {
}

void Transform::setRotation(forge::Quaternion newRot)
{

}

void Transform::setRotation(forge::Vector3 newRot)
{
}

void Transform::rotateX(float xRot)
{
}

void Transform::rotateY(float yRot)
{
}

void Transform::rotateZ(float zRot)
{
}

void Transform::setPosition(forge::Vector3 newPos)
{
}

void Transform::movePosition(forge::Vector3 offset)
{
}

void Transform::setPositionX(float newX)
{
}

void Transform::setPositionY(float newY)
{
}

void Transform::setPositionZ(float newZ)
{
}

void Transform::setScale(forge::Vector3 newScale)
{
}

void Transform::setScale(float scale)
{
}

void Transform::doScale(forge::Vector3 newScale)
{
}

void Transform::doScale(float scale)
{
}

forge::Quaternion Transform::getRotation()
{
	return rotation;
}

forge::Vector3 Transform::getRotationEuler()
{
	return forge::Vector3();
}

forge::Vector3 Transform::getPosition()
{
	return position;
}

forge::Vector3 Transform::getScale()
{
	return scale;
}
