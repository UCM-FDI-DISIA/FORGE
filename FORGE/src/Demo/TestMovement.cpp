#include "TestMovement.h"
#include "Input.h"
#include "Transform.h"
#include "ComponentData.h"
#include "Entity.h"
#include "AudioSource.h"
#include "MainForge.h"

const std::string TestMovement::id = "TestMovement";

TestMovement::TestMovement() :
	input(*Input::getInstance()),
	movement(10.0f),
	transform(nullptr),
	audio(nullptr) {
}

void TestMovement::initComponent(ComponentData* data) {
	transform = entity->getComponent<Transform>();
	audio = entity->getComponent<AudioSource>();
}

void TestMovement::update() {
	if (input.keyDown(K_P)) {
		audio->restart();
	}
	if (input.keyDown(K_W)) {
		transform->setPositionZ(transform->getPosition().getZ() + movement);
		std::cout << transform->getPosition().getX() << " " << transform->getPosition().getY() << " " << transform->getPosition().getZ() << "\n";
	}
	if (input.keyDown(K_S)) {
		transform->setPositionZ(transform->getPosition().getZ() - movement);
		std::cout << transform->getPosition().getX() << " " << transform->getPosition().getY() << " " << transform->getPosition().getZ() << "\n";

	}
	if (input.keyDown(K_D)) {
		transform->setPositionX(transform->getPosition().getX() + movement);
		std::cout << transform->getPosition().getX() << " " << transform->getPosition().getY() << " " << transform->getPosition().getZ() << "\n";
	}
	if (input.keyDown(K_A)) {
		transform->setPositionX(transform->getPosition().getX() - movement);
		std::cout << transform->getPosition().getX() << " " << transform->getPosition().getY() << " " << transform->getPosition().getZ() << "\n";
	}
	if (input.keyDown(K_RIGHT)) {
		transform->rotateY(10 * movement);
		std::cout << transform->getRotationEuler().getX() << " " << transform->getRotationEuler().getY() << " " << transform->getRotationEuler().getZ() << "\n";
	}
	if (input.keyDown(K_LEFT)) {
		transform->rotateY(-10 * movement);
		std::cout << transform->getRotationEuler().getX() << " " << transform->getRotationEuler().getY() << " " << transform->getRotationEuler().getZ() << "\n";
	}
	if (input.keyUp(K_ESC)) {
		MainForge::Exit();
	}
}
