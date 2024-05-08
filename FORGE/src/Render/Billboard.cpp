#include "Billboard.h"
#pragma warning(push)
#pragma warning(disable : 26439)
#pragma warning(disable : 26451)
#pragma warning(disable : 26495)
#pragma warning(disable : 4251)
#include <OgreBillboardSet.h>
#pragma warning(pop)
#include "Entity.h"
#include "RenderManager.h"
#include "Serializer.h"
#include "Random.h"

const std::string Billboard::id = "Billboard";

Billboard::Billboard() :
	size(1),
	billboardDimensions(1,1),
	totalDimensions(),
	material(""),
	billboardSet(nullptr), 
	renderManager(*RenderManager::GetInstance()) {
	serializer(size, "size");
	serializer(material, "material");
	serializer(billboardDimensions, "billboardDimensions");
	serializer(totalDimensions, "totalDimensions");
}

Billboard::~Billboard() {
	if(billboardSet != nullptr)
	{
		renderManager.removeNode(billboardSet);
	}
}

void Billboard::onEnabled() {
	billboardSet = renderManager.addBillboardNode(this);
	if (billboardSet != nullptr) {
		addBillboards();
	}
}

void Billboard::onDisabled() {
	renderManager.removeNode(billboardSet);
	billboardSet = nullptr;
}

bool Billboard::initComponent(ComponentData* data) {
	if (!entity->hasComponent("Transform")) {
		throwError(false, "Se requiere un componente Transform para generar un Billboard");
	}

	billboardSet = renderManager.addBillboardNode(this);
	if (billboardSet != nullptr) {
		addBillboards();
	}
	return true;
	return billboardSet != nullptr;
}

void Billboard::addBillboards() {
	forge::Random* rnd = forge::Random::GetInstance();
	float width = totalDimensions.getX();
	float height = totalDimensions.getY();
	float depth = totalDimensions.getZ();
	for (int i = 0; i < size; i++) {
		forge::Vector3 pos = forge::Vector3(rnd->generateRange(-width / 2.0f, width / 2.0f),
			rnd->generateRange(-height / 2.0f, height / 2.0f),
			rnd->generateRange(-depth / 2.0f, depth / 2.0f));
		billboardSet->createBillboard(pos);
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

void Billboard::setMaterial(std::string const& newMaterial) {
	material = newMaterial;
	billboardSet->setMaterialName(newMaterial);
}

void Billboard::setSize(int newSize) {
	size = newSize;
	billboardSet->setPoolSize(newSize);
}