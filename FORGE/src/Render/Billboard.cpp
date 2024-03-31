#include "Billboard.h"
#include "Entity.h"
#include "RenderManager.h"
#include "Serializer.h"
#include "OgreBillboardSet.h"
#include <Random.h>

const std::string Billboard::id = "Billboard";

Billboard::Billboard() :
	size(1),
	billboardDimensions(1,1),
	totalDimensions(),
	material(""),
	billboardSet(nullptr), 
	renderManager(nullptr) {
	serializer(size, "size");
	serializer(material, "material");
	serializer(billboardDimensions, "billboardDimensions");
	serializer(totalDimensions, "totalDimensions");
}

Billboard::~Billboard() {
	renderManager->removeNode(billboardSet);
}

void Billboard::onEnabled() {
	billboardSet = renderManager->addBillboardNode(this);
}

void Billboard::onDisabled() {
	renderManager->removeNode(billboardSet);
	billboardSet = nullptr;
}

void Billboard::initComponent(ComponentData* data) {
	if (entity->hasComponent("Transform")) {
		renderManager = RenderManager::getInstance();
		billboardSet = renderManager->addBillboardNode(this);
		addBillboards();
	}
}

void Billboard::addBillboards() {
	forge::Random* rnd = forge::Random::getInstance();
	float width = totalDimensions.getX();
	float height = totalDimensions.getY();
	float depth = totalDimensions.getZ();
	for (int i = 0; i < size; i++) {
		forge::Vector3 pos = forge::Vector3(rnd->generateRange(-width / 2.0f, width / 2.0f),
			rnd->generateRange(-height / 2.0f, height / 2.0f),
			rnd->generateRange(-depth / 2.0f, depth / 2.0f));
		billboardSet->createBillboard(pos);
	}
	delete rnd;
}

int Billboard::getSize() {
	return size;
}

float Billboard::getBillboardWidth() {
	return billboardDimensions.getX();
}

float Billboard::getBillboardHeight() {
	return billboardDimensions.getY();
}

std::string Billboard::getMaterial() {
	return material;
}

void Billboard::setMaterial(std::string newMaterial) {
	material = newMaterial;
	billboardSet->setMaterialName(newMaterial);
}

void Billboard::setSize(int newSize) {
	size = newSize;
	billboardSet->setPoolSize(newSize);
}