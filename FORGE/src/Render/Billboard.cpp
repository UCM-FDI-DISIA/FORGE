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
	bSet(nullptr), 
	renderManager(nullptr) {
	serializer(size, "size");
	serializer(material, "material");
	serializer(billboardDimensions, "billboardDimensions");
	serializer(totalDimensions, "totalDimensions");
}

Billboard::~Billboard() {
	renderManager->removeNode(bSet);
}

void Billboard::onEnabled() {
	bSet = renderManager->addBillboardNode(this);
}

void Billboard::onDisabled() {
	renderManager->removeNode(bSet);
	bSet = nullptr;
}

void Billboard::initComponent(ComponentData* data) {
	if (entity->hasComponent("Transform")) {
		renderManager = RenderManager::getInstance();
		bSet = renderManager->addBillboardNode(this);
		addBillboards();
	}
}

void Billboard::addBillboards() {
	forge::Random* rn = new forge::Random();
	float width = totalDimensions.getX();
	float height = totalDimensions.getY();
	float depth = totalDimensions.getZ();
	for (int i = 0; i < size; i++) {
		forge::Vector3 pos = forge::Vector3(rn->generateRange(-width / 2.0f, width / 2.0f), 
			rn->generateRange(-height / 2.0f, height / 2.0f),
			rn->generateRange(-depth / 2.0f, depth / 2.0f));
		bSet->createBillboard(pos);
	}
	delete rn;
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
	bSet->setMaterialName(newMaterial);
}

void Billboard::setSize(int newSize) {
	size = newSize;
	bSet->setPoolSize(newSize);
}