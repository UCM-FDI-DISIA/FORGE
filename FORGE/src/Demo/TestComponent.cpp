#include "TestComponent.h"
#include "lua.hpp"
#include "LuaBridge/LuaBridge.h"
#include "LuaForge.h"
#include "Input.h"
#include "Transform.h"
#include "ComponentData.h"
#include "Entity.h"
#include "Animator.h"
#include "SceneManager.h"
#include "AudioSource.h"
#include "RigidBody.h"
#include "Collider.h"
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
	if (entity->hasComponent<Transform>() && entity->hasComponent<AudioSource>() 
		&& entity->hasComponent<Animator>() && entity->hasComponent<RigidBody>()) {
		transform = entity->getComponent<Transform>();	
		audio = entity->getComponent<AudioSource>();	
		animator = entity->getComponent<Animator>();
		rigidBody = entity->getComponent<RigidBody>();

		rigidBody->registerCallback(Collider::onCollisionEnter, [this] (Collider* me, Collider* other) {
			std::cerr << "Colision Iniciada" << std::endl;
		});

		rigidBody->registerCallback(Collider::onCollisionStay, [this] (Collider* me, Collider* other) {
			std::cerr << "Colision Continuada" << std::endl;
		});

		rigidBody->registerCallback(Collider::onCollisionLeave, [this] (Collider* me, Collider* other) {
			std::cerr << "Colision Finalizada" << std::endl;
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
	if (input.keyDown(K_O)) {
		sceneManager->instantiateBlueprint("obstaculo", entity);
	}
	if (input.keyDown(K_W)) {
		//transform->setPositionZ(transform->getPosition().getZ() + movement);
		rigidBody->setPositionZ(transform->getPosition().getZ() + movement);
	}

	if (input.keyPressed(K_W)) {
		//transform->setPositionZ(transform->getPosition().getZ() + movement);
		rigidBody->setPositionZ(transform->getPosition().getZ() + movement);
	}
	if (input.keyPressed(K_S)) {
		//transform->setPositionZ(transform->getPosition().getZ() - movement);
		rigidBody->setPositionZ(transform->getPosition().getZ() - movement);

	}
	if (input.keyPressed(K_D)) {
		//transform->setPositionX(transform->getPosition().getX() + movement);
		rigidBody->setPositionX(transform->getPosition().getX() + movement);
	}
	if (input.keyPressed(K_A)) {
		//transform->setPositionX(transform->getPosition().getX() - movement);
		rigidBody->setPositionX(transform->getPosition().getX() - movement);
	}
	if (input.keyPressed(K_RIGHT)) {
		//transform->rotateY(movement);
		rigidBody->rotateY(movement);
	}
	if (input.keyPressed(K_LEFT)) {
		//transform->rotateY(-movement);
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
	std::cout << "SE LLAMO AL CALLBACK\n";
}