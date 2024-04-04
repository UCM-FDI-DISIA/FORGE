#pragma once
#ifndef MESH_H_
#define MESH_H_
#include <Component.h>
#include <string>

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

    static const std::string id;
public:
    static std::string const& Id();

	Mesh();
    
    ~Mesh();

    void initComponent(ComponentData* data) override;

	#pragma region setters
    void setMesh(std::string newMesh);
    void setMaterial(std::string newMaterial);
	#pragma endregion

	#pragma region getters
    const std::string& getMesh() const;
    const std::string& getMaterial() const;
	#pragma endregion
};

#endif // !MESH_H_