#include "Mesh.h"
#include "RenderManager.h"
#include "Entity.h"
#include "Serializer.h"
#include "Animator.h"
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
    renderManager->removeNode(ogreEntity);
}

void Mesh::initComponent(ComponentData* data) {
    if(entity->hasComponent("Transform")) {
        renderManager = RenderManager::getInstance();
        ogreEntity = renderManager->addMeshNode(this);
    }
}

void Mesh::setEnabled(bool newActive) {
    Component::setEnabled(newActive);
    if (newActive) {
        ogreEntity = renderManager->addMeshNode(this);
    }
    else {
        renderManager->removeNode(ogreEntity);
        ogreEntity = nullptr;
    }
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