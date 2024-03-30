#pragma once
#ifndef TEST_MOVEMENT_H_
#define TEST_MOVEMENT_H_
#include "Component.h"
#include <string>
#include <vector>
class Input;
class Transform;
class Animator;
class TestMovement : public Component {
private:
	Transform* transform;
	Animator* animator;
	Input& input;
	float movement;
	std::vector<std::string> anims;
	int activeAnim;
public:
	static const std::string id;

	TestMovement();
	bool initComponent(ComponentData* data) override;
	void update() override;

};

#endif // !TEST_MOVEMENT_H_