#include "Mesh.h"
#include "RenderManager.h"
#include "Entity.h"
#include "Serializer.h"
#include "OgreEntity.h"

const std::string Mesh::id = "Mesh";

Mesh::Mesh() : 
	mesh(),
	material(),
    ogreEntity(nullptr),
    renderManager(nullptr) {
	serializer(mesh, "mesh");
	serializer(material, "material");
}

Mesh::~Mesh() {
    if(ogreEntity != nullptr) renderManager->removeNode(ogreEntity);
}

bool Mesh::initComponent(ComponentData* data) {
    if(entity->hasComponent("Transform")) {
        renderManager = RenderManager::getInstance();
        ogreEntity = renderManager->addMeshNode(this);
    }
    return ogreEntity != nullptr;
}

void Mesh::setMesh(std::string newMesh) {
    mesh = newMesh;
    ogreEntity = renderManager->updateMeshNode(ogreEntity, this);
}

void Mesh::setMaterial(std::string newMaterial) {
    material = newMaterial;
    ogreEntity->setMaterialName(newMaterial);
}

const std::string& Mesh::getMesh() const {
    return mesh;
}

const std::string& Mesh::getMaterial() const {
    return material;
}