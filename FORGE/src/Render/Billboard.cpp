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
#include "Transform.h"

const std::string Billboard::id = "Billboard";

Billboard::Billboard() :
	billboardDimensions(1,1),
	material(""),
	billboardSet(nullptr), 
	renderManager(*RenderManager::GetInstance()),
	transform(nullptr) {
	serializer(material, "material");
	serializer(billboardDimensions, "billboardDimensions");
}

Billboard::~Billboard() {
	if(billboardSet != nullptr) {
		renderManager.removeNode(billboardSet);
	}
}

void Billboard::onEnabled() {
	createBillboard();
}

void Billboard::onDisabled() {
	renderManager.removeNode(billboardSet);
	billboardSet = nullptr;
}

bool Billboard::initComponent(ComponentData* data) {
	if (!entity->hasComponent(Transform::id)) {
		throwError(false, "Se requiere un componente Transform para generar un Billboard");
	}
	transform = entity->getComponent<Transform>();
	createBillboard();
	return true;
}

bool Billboard::createBillboard() {
	billboardSet = renderManager.addBillboardNode(this);
	if (billboardSet != nullptr) {
		billboardSet->createBillboard(renderManager.forgeVector3ToOgreVector3(transform->getGlobalPosition()));
		return true;
	}
	return false;
}

int Billboard::getSize() {
	return 1;
}

float Billboard::getBillboardWidth() {
	return billboardDimensions.getX();
}

float Billboard::getBillboardHeight() {
	return billboardDimensions.getY();
}

std::string const& Billboard::getMaterial() {
	return material;
}

void Billboard::setMaterial(std::string const& newMaterial) {
	material = newMaterial;
	billboardSet->setMaterialName(newMaterial);
}