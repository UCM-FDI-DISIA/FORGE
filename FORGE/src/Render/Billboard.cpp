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

void Billboard::setEnabled(bool newActive) {
	Component::setEnabled(newActive);
	if (newActive) {
		bSet = renderManager->addBillboardNode(this);
	}
	else {
		renderManager->removeNode(bSet);
		bSet = nullptr;
	}
}

bool Billboard::initComponent(ComponentData* data) {
	if (entity->hasComponent("Transform")) {
		renderManager = RenderManager::getInstance();
		bSet = renderManager->addBillboardNode(this);
		addBillboards();
		return true;
	}
	return false;
}

void Billboard::addBillboards() {
	forge::Random* rn = new forge::Random();
	int width = (int)totalDimensions.getX();
	int height = (int)totalDimensions.getY();
	int depth = (int)totalDimensions.getZ();
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