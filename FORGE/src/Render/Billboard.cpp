#include "Billboard.h"
#include "Entity.h"
#include "RenderManager.h"
#include "Serializer.h"
#include "OgreBillboardSet.h"

const std::string Billboard::id = "Billboard";

Billboard::Billboard() :
	size(20),
	billboardDimensions(),
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

void Billboard::initComponent(ComponentData* data) {
	if (entity->hasComponent("Transform")) {
		renderManager = RenderManager::getInstance();
		bSet = renderManager->addBillboardNode(this);
		addBillboards();
	}
}

void Billboard::addBillboards() {
	int width = totalDimensions.getX();
	int height = totalDimensions.getY();
	int depth = totalDimensions.getZ();
	for (int i = 0; i < size; i++) {
		forge::Vector3 pos = forge::Vector3(rand() % width - width / 2, 
			rand() % height - height / 2, 
			rand() % depth - depth / 2);
		bSet->createBillboard(pos);
	}
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