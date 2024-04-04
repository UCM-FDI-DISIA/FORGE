#include "RectTransform.h"
#include "Serializer.h"
using namespace forge;

const std::string RectTransform::id = "Transform";

RectTransform::RectTransform() :
	position(),
	scale(1, 1),
	needsUpdate(true) {
	serializer(position, "position");
	serializer(scale, "scale");
}

void RectTransform::setPosition(forge::Vector2 const& newPos) {
	position = newPos;
	needsUpdate = true;
}

void RectTransform::movePosition(forge::Vector2 const& offset) {
	position += offset;
	needsUpdate = true;
}

void RectTransform::setPositionX(float newX) {
	position.setX(newX);
	needsUpdate = true;
}

void RectTransform::setPositionY(float newY) {
	position.setY(newY);
	needsUpdate = true;
}

void RectTransform::setScale(forge::Vector2 const& newScale) {
	scale = newScale;
	needsUpdate = true;
}

void RectTransform::setScale(float newScale) {
	scale = Vector2(newScale);
	needsUpdate = true;
}

void RectTransform::doScale(forge::Vector2 const& rescale) {
	scale *= rescale;
	needsUpdate = true;
}

void RectTransform::doScale(float rescale) {
	scale *= rescale;
	needsUpdate = true;
}

void RectTransform::setNeedsUpdate(bool needed) {
	needsUpdate = needed;
}

forge::Vector2 const& RectTransform::getPosition() const {
	return position;
}

forge::Vector2 const& RectTransform::getScale() const {
	return scale;
}

bool RectTransform::getNeedsUpdate() const {
	return needsUpdate;
}