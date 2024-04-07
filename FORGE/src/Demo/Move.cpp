#include "Move.h"
#include "ComponentData.h"
#include "Serializer.h"
#include "RigidBody.h"
#include "Entity.h"

const std::string Move::id = "Move";

Move::Move() {

}

bool Move::initComponent(ComponentData* data) {
	if (rb = entity->getComponent<RigidBody>()) {
	movement = data->get<float>("speed");
	return true;
	}
	return false;
}

void Move::update() {
	if (!rb->isTrigger()) {
	rb->setTrigger(true);
	}
	rb->applyForce(forge::Vector3(0, movement, 0));

}