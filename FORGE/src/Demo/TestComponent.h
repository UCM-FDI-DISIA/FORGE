#pragma once
#ifndef TEST_MOVEMENT_H_
#define TEST_MOVEMENT_H_
#include "Component.h"
#include <string>
#include <vector>
class Input;
class Transform;
class Animator;
class AudioSource;
class SceneManager;
class RigidBody;

class TestComponent : public Component {
private:
	Transform* transform;
	Animator* animator;
	RigidBody* rigidBody;
	Input& input;
	float movement;
	std::vector<std::string> anims;
	int activeAnim;
	AudioSource* audio;
	SceneManager* sceneManager;
public:
	static const std::string id;

	TestComponent();
	bool initComponent(ComponentData* data) override;
	void update() override;

};

#endif // !TEST_MOVEMENT_H_