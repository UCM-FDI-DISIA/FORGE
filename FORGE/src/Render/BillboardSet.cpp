#include "BillboardSet.h"
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
#include "Random.h"

const std::string BillboardSet::id = "BillboardSet";

bool BillboardSet::addBillboards(int number) {
	if (billboardSet == nullptr) {
		billboardSet = renderManager.addBillboardNode(this);
		if (billboardSet == nullptr) {
			throwError(false, "No se ha podido crear el nodo para el BillboardSet");
		}
	}
	forge::Random* rnd = forge::Random::GetInstance();
	float width = totalDimensions.getX();
	float height = totalDimensions.getY();
	float depth = totalDimensions.getZ();
	for (int i = 0; i < number; i++) {
		forge::Vector3 pos = forge::Vector3(rnd->generateRange(-width / 2.0f, width / 2.0f),
			rnd->generateRange(-height / 2.0f, height / 2.0f),
			rnd->generateRange(-depth / 2.0f, depth / 2.0f));
		billboardSet->createBillboard(renderManager.forgeVector3ToOgreVector3(pos));
	}
	return true;
}

BillboardSet::BillboardSet() : 
	size(2),
	totalDimensions(1) {
	serializer(size, "size");
	serializer(totalDimensions, "totalDimensions");
}

 void BillboardSet::onEnabled() {
	 addBillboards(size);
}

bool BillboardSet::initComponent(ComponentData* data) {
	if (!entity->hasComponent(Transform::id)) {
		throwError(false, "Se requiere un componente Transform para generar un BillboardSet");
	}
	if (entity->hasComponent(Billboard::id)) {
		throwError(false, "No se puede tener un componente BillboardSet y un componente Billboard en la misma entidad");
	}
	transform = entity->getComponent<Transform>();
	return addBillboards(size);
}

int const& BillboardSet::getSize() const {
	return size;
}

void BillboardSet::setSize(int newSize) {
	addBillboards(size - newSize);
	size = newSize;
}