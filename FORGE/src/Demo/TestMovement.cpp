#include "TestMovement.h"
#include "Input.h"
#include "Transform.h"
#include "ComponentData.h"
#include "Entity.h"

const std::string TestMovement::id = "TestMovement";

TestMovement::TestMovement() :
	input(*Input::getInstance()),
	movement(2.0f) {
}

bool TestMovement::initComponent(ComponentData* data) {
	transform = entity->getComponent<Transform>();
	return transform != nullptr;
}

void TestMovement::update() {
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
		transform->rotateY(10 * movement);
	}
	if (input.keyPressed(K_LEFT)) {
		transform->rotateY(-10 * movement);
	}
}
