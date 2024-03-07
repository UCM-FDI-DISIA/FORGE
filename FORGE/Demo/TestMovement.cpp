#include "TestMovement.h"
#include "Input.h"
#include "Transform.h"
#include "ComponentData.h"
#include "Entity.h"

const std::string TestMovement::id = "TestMovement";

TestMovement::TestMovement() :
	input(*Input::getInstance()),
	movement(10.0f) {
}

void TestMovement::initComponent(ComponentData* data) {
	transform = entity->getComponent<Transform>();
}

void TestMovement::update() {
	if (input.keyDown(K_W)) {
		transform->setPositionZ(transform->getPosition().getZ() + movement);
	}
	if (input.keyDown(K_S)) {
		transform->setPositionZ(transform->getPosition().getZ() - movement);
	}
	if (input.keyDown(K_D)) {
		transform->setPositionZ(transform->getPosition().getX() + movement);
	}
	if (input.keyDown(K_A)) {
		transform->setPositionZ(transform->getPosition().getX() - movement);
	}
	if (input.keyDown(K_RIGHT)) {
		transform->rotateY(movement);
	}
	if (input.keyDown(K_LEFT)) {
		transform->rotateY(-movement);
	}
}
