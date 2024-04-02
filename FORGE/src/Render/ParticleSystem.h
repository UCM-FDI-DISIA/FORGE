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
    #pragma region Constructores
    ParticleSystem();
    ~ParticleSystem();
    #pragma endregion

    void initComponent(ComponentData* data) override;

    void onEnabled() override;

    void onDisabled() override;

	#pragma region Getters
    /// <summary>
    /// Acceso a la particula que esta siendo emitida
    /// </summary>
    /// <returns>El nombre de la particula en uso</returns>
    const std::string& getParticle() const;
    /// <summary>
    /// Acceso al estado de emision del sistema
    /// </summary>
    /// <returns>Estado de emision actual</returns>
    const bool& getEmitting() const;
	#pragma endregion

    #pragma region Setters
    /// <summary>
    /// Cambia la particula a emitir por el sistema
    /// </summary>
    /// <param name="newParticle">La nueva particula</param>
    void setParticle(std::string newParticle);
    /// <summary>
    /// Cambia el estado de emision del sistema de particulas
    /// </summary>
    /// <param name="newEmitting">Estado nuevo de emision</param>
    void setEmitting(bool newEmitting);
    #pragma endregion
};

#endif // !PARTICLESYSTEM_H_