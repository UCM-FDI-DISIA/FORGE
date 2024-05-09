#include "TestComponent.h"
#include "Input.h"
#include "Transform.h"
#include "ComponentData.h"
#include "Entity.h"
#include "Animator.h"
#include "SceneManager.h"
#include "AudioSource.h"
#include "RigidBody.h"
#include "Collider.h"
#include "Invoker.h"

const std::string TestComponent::id = "TestComponent";

TestComponent::TestComponent() :
	input(*Input::GetInstance()),
	movement(2.0f),
	transform(nullptr),
	animator(nullptr),
	audio(nullptr),
	rigidBody(nullptr),
	sceneManager(SceneManager::GetInstance()),
	anims(),
	activeAnim(0) {
}

bool TestComponent::initComponent(ComponentData* data) {
	entity->getInvoker().registerFunction("Poto", [&] () {
		Poto();
		});
	if (entity->hasComponent<Transform>() && entity->hasComponent<AudioSource>() 
		&& entity->hasComponent<Animator>() && entity->hasComponent<RigidBody>()) {
		transform = entity->getComponent<Transform>();	
		audio = entity->getComponent<AudioSource>();	
		animator = entity->getComponent<Animator>();
		rigidBody = entity->getComponent<RigidBody>();

		rigidBody->registerCallback(forge::onCollisionEnter, [this] (Collider* me, Collider* other) {
			std::cout << "Colision Iniciada" << std::endl;
		});

		rigidBody->registerCallback(forge::onCollisionStay, [this] (Collider* me, Collider* other) {
			std::cout << "Colision Continuada" << std::endl;
		});

		rigidBody->registerCallback(forge::onCollisionLeave, [this] (Collider* me, Collider* other) {
			std::cout << "Colision Finalizada" << std::endl;
		});

		if (animator != nullptr && animator->getEntity()->isAlive()) {
			anims = animator->getAnimations();
			animator->setLoop(anims, true);
			return true;
		}

	}
	std::cerr << "ERROR: Se necesita un componente Transform, RigidBody, AudioSource y Animator para generar un TestComponent\n";
	return false;
}

void TestComponent::update() {
	if (anims.size() <= 0) {
		anims = animator->getAnimations();
		animator->setLoop(anims, true);
	}
	if (input.keyPressed(K_Q)) {
		if (activeAnim <= 0) {
			activeAnim = static_cast<int>(anims.size());
		}
		activeAnim--;
		animator->changeActive(anims[activeAnim]);
	}
	if (input.keyPressed(K_E)) {
		activeAnim++;
		if (activeAnim >= static_cast<int>(anims.size())) {
			activeAnim = 0;
		}
		animator->changeActive(anims[activeAnim]);
	}
	if (input.keyDown(K_P)) {
		audio->restart();
	}
	if (input.keyDown(K_O)) {
		sceneManager->instantiateBlueprint("obstaculo", entity);
	}
	if (input.keyDown(K_W)) {
		rigidBody->setLinearVelocity(forge::Vector3(0,1,0));
	}

	if (input.keyPressed(K_W)) {
		rigidBody->setLinearVelocity(forge::Vector3(0, 1, 0));
	}
	if (input.keyPressed(K_S)) {
		rigidBody->setPositionZ(transform->getPosition().getZ() - movement);

	}
	if (input.keyPressed(K_D)) {
		rigidBody->setPositionX(transform->getPosition().getX() + movement);
	}
	if (input.keyPressed(K_A)) {
		rigidBody->setPositionX(transform->getPosition().getX() - movement);
	}
	if (input.keyPressed(K_RIGHT)) {
		rigidBody->rotateY(movement);
	}
	if (input.keyPressed(K_LEFT)) {
		rigidBody->rotateY(-movement);
	}

	if (input.keyDown(K_R)) {
		std::cout << "\nHOLA\n";
		if (sceneManager->getActiveSceneId() == "Test") {
			sceneManager->changeScene("Play");
		}
		else sceneManager->changeScene("Test");
	}
}

void TestComponent::Poto() {
	std::cout << "Poto en C++\n";
}