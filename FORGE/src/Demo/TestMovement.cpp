﻿#include "TestMovement.h"
#include "Input.h"
#include "Transform.h"
#include "ComponentData.h"
#include "Entity.h"

const std::string TestMovement::id = "TestMovement";

TestMovement::TestMovement() :
	input(*Input::getInstance()),
	movement(2.0f) {
}

void TestMovement::initComponent(ComponentData* data) {
	transform = entity->getComponent<Transform>();
}

void TestMovement::update() {
	if (input.keyPressed(K_W)) {
		transform->setPositionZ(transform->getPosition().getZ() + movement);
		std::cout << transform->getPosition().getX() << " " << transform->getPosition().getY() << " " << transform->getPosition().getZ() << "\n";
	}
	if (input.keyPressed(K_S)) {
		transform->setPositionZ(transform->getPosition().getZ() - movement);
		std::cout << transform->getPosition().getX() << " " << transform->getPosition().getY() << " " << transform->getPosition().getZ() << "\n";

	}
	if (input.keyPressed(K_D)) {
		transform->setPositionX(transform->getPosition().getX() + movement);
		std::cout << transform->getPosition().getX() << " " << transform->getPosition().getY() << " " << transform->getPosition().getZ() << "\n";
	}
	if (input.keyPressed(K_A)) {
		transform->setPositionX(transform->getPosition().getX() - movement);
		std::cout << transform->getPosition().getX() << " " << transform->getPosition().getY() << " " << transform->getPosition().getZ() << "\n";
	}
	if (input.keyPressed(K_RIGHT)) {
		transform->rotateY(10 * movement);
		std::cout << transform->getRotationEuler().getX() << " " << transform->getRotationEuler().getY() << " " << transform->getRotationEuler().getZ() << "\n";
	}
	if (input.keyPressed(K_LEFT)) {
		transform->rotateY(-10 * movement);
		std::cout << transform->getRotationEuler().getX() << " " << transform->getRotationEuler().getY() << " " << transform->getRotationEuler().getZ() << "\n";
	}
}
