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

Mesh::Mesh() :
	mesh(),
	material(),
    ogreEntity(nullptr),
    renderManager(nullptr) {
	serializer(mesh, "mesh");
	serializer(material, "material");
}

Mesh::~Mesh() {
    if(ogreEntity != nullptr && renderManager != nullptr) 
    {
        renderManager->removeNode(ogreEntity);
    }
}

bool Mesh::initComponent(ComponentData* data) {
    if(entity->hasComponent("Transform")) {
        renderManager = RenderManager::getInstance();
        ogreEntity = renderManager->addMeshNode(this);
    }
    else 
    {
        std::cerr << "ERROR: Se requiere un componente Transform para generar un Mesh\n";
    }
    return ogreEntity != nullptr;
}

void Mesh::onEnabled() {
    ogreEntity = renderManager->addMeshNode(this);
}

void Mesh::onDisabled() {
    renderManager->removeNode(ogreEntity);
    ogreEntity = nullptr;
}

void Mesh::setMesh(std::string const& newMesh) {
    mesh = newMesh;
    ogreEntity = renderManager->updateMeshNode(ogreEntity, this);
}

void Mesh::setMaterial(std::string const& newMaterial) {
    material = newMaterial;
    ogreEntity->setMaterialName(newMaterial);
}


const std::string& Mesh::getMesh() const {
    return mesh;
}

const std::string& Mesh::getMaterial() const {
    return material;
}