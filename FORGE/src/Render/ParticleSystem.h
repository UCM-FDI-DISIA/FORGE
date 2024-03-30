#pragma once
#ifndef PARTICLESYSTEM_H_
#define PARTICLESYSTEM_H_
#include <Component.h>
#include <string>

class RenderManager;
namespace Ogre {
    class ParticleSystem;
}

class ParticleSystem : public Component {
protected:
    std::string particle;
    bool emitting;
    Ogre::ParticleSystem* ogreParticleSystem;
    RenderManager* renderManager; 

public:
	static const std::string id;

    ParticleSystem();
    
    ~ParticleSystem();

    void initComponent(ComponentData* data) override;

    void onEnabled() override;

    void onDisabled() override;

	#pragma region setters
    void setParticle(std::string newParticle);
    void setEmitting(bool newEmitting);
	#pragma endregion

	#pragma region getters
    const std::string& getParticle() const;
    const bool& getEmitting() const;
	#pragma endregion
};

#endif // !PARTICLESYSTEM_H_