#pragma once
#ifndef ANIMATOR_H_
#define ANIMATOR_H_
#include <Component.h>
#include <string>
#include <list>

class RenderManager;
namespace Ogre {
    class Entity;
}

class Animator : public Component {
private:
    std::list <std::string > activeAnimations;
    Ogre::AnimationStateSet* ogreEntity;
    RenderManager* renderManager;

public:
    static const std::string id;
    Animator();

    ~Animator();

    void initComponent(ComponentData* data) override;

    void setEnabled(bool newActive) override;

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