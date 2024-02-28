#pragma once
#ifndef TRANSFORM_H_
#define TRANSFORM_H_

#include <string>
#include <vector>
#include "Component.h"

namespace forge {
	struct Vector3 { float x; float y; float z; };
	struct Quaternion { float x; float y; float z; float w;};
}

class Transform : public Component {
private:
	forge::Vector3 position;
	forge::Quaternion rotation;
	forge::Vector3 scale;
protected:

public:
	Transform();

	void initComponent(ComponentData* data) override;

	void setRotation(forge::Quaternion newRot);
	void setRotation(forge::Vector3 newRot);
	void rotateX(float xRot);
	void rotateY(float yRot);
	void rotateZ(float zRot);

	void setPosition(forge::Vector3 newPos);
	void movePosition(forge::Vector3 offset);
	void setPositionX(float newX);
	void setPositionY(float newY);
	void setPositionZ(float newZ);

	void setScale(forge::Vector3 newScale);
	void setScale(float scale);
	void doScale(forge::Vector3 newScale);
	void doScale(float scale);

	forge::Quaternion getRotation();
	forge::Vector3 getRotationEuler();
	forge::Vector3 getPosition();
	forge::Vector3 getScale();

};

#endif // !TRANSFORM_H_