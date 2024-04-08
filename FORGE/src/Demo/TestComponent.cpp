﻿#include "TestComponent.h"
#include "Input.h"
#include "Transform.h"
#include "ComponentData.h"
#include "Entity.h"
#include "Animator.h"
#include "SceneManager.h"
#include "AudioSource.h"

const std::string TestComponent::id = "TestComponent";

TestComponent::TestComponent() :
	input(*Input::GetInstance()),
	movement(2.0f),
	transform(nullptr),
	animator(nullptr),
	audio(nullptr),
	sceneManager(SceneManager::GetInstance()),
	anims(),
	activeAnim(0) {
}

bool TestComponent::initComponent(ComponentData* data) {
	if (entity->hasComponent<Transform>() && entity->hasComponent<AudioSource>() && entity->hasComponent<Animator>()) {
		transform = entity->getComponent<Transform>();	
		audio = entity->getComponent<AudioSource>();	
		animator = entity->getComponent<Animator>();
		if (animator != nullptr && animator->getEntity()->isAlive()) {
			anims = animator->getAnimations();
			animator->setLoop(anims, true);
			return true;
		}
	}
	throwError(false, "Se necesita un componente Transform, AudioSource y Animator para generar un TestComponent");
}

void TestComponent::update() {
	if (input.keyPressed(K_Q) && anims.size() > 0) {
		if (activeAnim <= 0) {
			activeAnim = anims.size();
		}
		activeAnim--;
		animator->changeActive(anims[activeAnim]);
	}
	if (input.keyPressed(K_E) && anims.size() > 0) {
		activeAnim++;
		if (activeAnim >= anims.size()) {
			activeAnim = 0;
		}
		animator->changeActive(anims[activeAnim]);
	}
	if (input.keyDown(K_P)) {
		audio->restart();
	}
	if (input.keyDown(K_W)) {
		transform->setPositionZ(transform->getPosition().getZ() + movement);
	}

	if (input.keyPressed(K_W)) {
		transform->setPositionZ(transform->getPosition().getZ() + movement);
	}
	if (input.keyPressed(K_S)) {
		transform->setPositionZ(transform->getPosition().getZ() - movement);

	}
	if (input.keyPressed(K_D)) {
		transform->setPositionX(transform->getPosition().getX() + movement);
	}
	if (input.keyPressed(K_A)) {
		transform->setPositionX(transform->getPosition().getX() - movement);
	}
	if (input.keyPressed(K_RIGHT)) {
		transform->rotateY(movement);
	}
	if (input.keyPressed(K_LEFT)) {
		transform->rotateY(-movement);
	}

	if (input.keyDown(K_R)) {
		if (sceneManager->getActiveSceneId() == "Test") {
			sceneManager->changeScene("Play");
		}
		else sceneManager->changeScene("Test");
	}
}
