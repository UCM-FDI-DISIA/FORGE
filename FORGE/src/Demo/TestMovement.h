#pragma once
#ifndef TEST_MOVEMENT_H_
#define TEST_MOVEMENT_H_
#include "Component.h"
#include <string>
class Input;
class Transform;
class TestMovement : public Component {
private:
	Transform* transform;
	Input& input;
	float movement;
public:
	static const std::string id;

	TestMovement();
	void initComponent(ComponentData* data) override;
	void update() override;

};

#endif // !TEST_MOVEMENT_H_