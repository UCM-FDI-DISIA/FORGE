#include "Move.h"
#include "ComponentData.h"
#include "Serializer.h"
#include "RigidBody.h"
#include "Entity.h"

const std::string Move::id = "Move";

Move::Move() {

}

void Move::initComponent(ComponentData* data) {
	rb = entity->getComponent<RigidBody>();
	movement = data->get<float>("speed");
}

void Move::update() {
	if (!rb->isTrigger()) {
	rb->setTrigger(true);
	}
	rb->applyForce(forge::Vector3(0, movement, 0));

}