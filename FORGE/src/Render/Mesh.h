#pragma once
#ifndef MESH_H_
#define MESH_H_
#include <Component.h>
#include <string>
#include "ForgeExport.h"

class RenderManager;
namespace Ogre {
    class Entity;
}

class Mesh : public Component {
private:
    std::string mesh;
    std::string material;
    Ogre::Entity* ogreEntity;
    RenderManager* renderManager; 

public:
    static const FORGE_API_VAR std::string id;

    FORGE_API Mesh();
    
    FORGE_API ~Mesh();

    FORGE_API void initComponent(ComponentData* data) override;

	#pragma region setters
    FORGE_API void setMesh(std::string newMesh);
    FORGE_API void setMaterial(std::string newMaterial);
	#pragma endregion

	#pragma region getters
    const FORGE_API std::string& getMesh() const;
    const FORGE_API std::string& getMaterial() const;
	#pragma endregion
};

#endif // !MESH_H_