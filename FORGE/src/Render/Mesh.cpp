#include "Mesh.h"
#include "RenderManager.h"
#include "Entity.h"
#include "Serializer.h"
#pragma warning(push)
#pragma warning(disable : 4251)
#pragma warning(disable : 26439)
#pragma warning(disable : 26451)
#pragma warning(disable : 26495)
#include <OgreEntity.h>
#pragma warning(pop)

const std::string Mesh::id = "Mesh";

std::string const& Mesh::Id() {
    return id;
}

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