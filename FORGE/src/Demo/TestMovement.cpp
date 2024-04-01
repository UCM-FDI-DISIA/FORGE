#include "TestComponent.h"
#include "Input.h"
#include "Transform.h"
#include "ComponentData.h"
#include "Entity.h"
#include "Animator.h"
#include "SceneManager.h"
#include "AudioSource.h"

const std::string TestComponent::id = "TestComponent";

TestComponent::TestComponent() :
	input(*Input::getInstance()),
	movement(2.0f),
	transform(nullptr),
	animator(nullptr),
	anims(),
	activeAnim(0),
	movement(10.0f),
	transform(nullptr),
	audio(nullptr) {
}

void TestComponent::initComponent(ComponentData* data) {
	transform = entity->getComponent<Transform>();
	audio = entity->getComponent<AudioSource>();
	animator = entity->getComponent<Animator>();
	if (animator != nullptr) {
		anims = animator->getAnimations();
	}
}

void TestComponent::update() {
	if (input.keyPressed(K_Q)) {
		if (activeAnim <= 0) {
			activeAnim = anims.size();
		}
		activeAnim--;
		animator->changeActive(anims[activeAnim]);
	}
	if (input.keyPressed(K_E)) {
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
		std::cout << transform->getPosition().getX() << " " << transform->getPosition().getY() << " " << transform->getPosition().getZ() << "\n";
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
		SceneManager::getInstance()->changeScene("Play");
	}
}
