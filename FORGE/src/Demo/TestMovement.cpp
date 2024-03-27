#include "TestMovement.h"
#include "Input.h"
#include "Transform.h"
#include "ComponentData.h"
#include "Entity.h"
#include "Animator.h"
#include "SceneManager.h"

const std::string TestMovement::id = "TestMovement";

TestMovement::TestMovement() :
	input(*Input::getInstance()),
	movement(2.0f),
	transform(nullptr),
	animator(nullptr),
	anims(),
	activeAnim(0){
}

void TestMovement::initComponent(ComponentData* data) {
	transform = entity->getComponent<Transform>();
	if (entity->hasComponent("Animator")) animator = entity->getComponent<Animator>();
}

void TestMovement::update() {
	if (animator != nullptr) {
		anims = animator->getAnimations();

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
