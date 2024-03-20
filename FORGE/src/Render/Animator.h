#pragma once
#ifndef ANIMATOR_H_
#define ANIMATOR_H_
#include "Mesh.h"
#include <string>
#include <vector>
#include <unordered_set>

class RenderManager;
namespace Ogre {
    class AnimationStateSet;
}

class Animator : public Mesh {
    std::unordered_set<std::string> activeAnimations;
    Ogre::AnimationStateSet* ogreAnimations;

public:
    static const std::string id;

    Animator();

    ~Animator();

    void initComponent(ComponentData* data) override;

    void update() override;

    #pragma region setters
    void setLoop(std::string animation, bool looped);
    void setActive(std::string animation, bool active);
    void setLoop(std::vector<std::string> animations, bool looped);
    void setActive(std::vector<std::string> activeAnimations, bool active);
    void changeActive(std::string animation);
    void changeActive(std::vector<std::string> activeAnimations);
    #pragma endregion

    #pragma region getters
    std::vector<std::string> getAnimations();
    std::unordered_set<std::string> getActiveAnimations();
    #pragma endregion
};

#endif // !MESH_H_