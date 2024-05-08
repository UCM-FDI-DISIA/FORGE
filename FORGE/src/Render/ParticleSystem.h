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
    RenderManager& renderManager; 

public:
	FORGE_API_VAR static const std::string id;
    #pragma region Constructores
    FORGE_API ParticleSystem();
    FORGE_API ~ParticleSystem();
    #pragma endregion

    FORGE_API bool initComponent(ComponentData* data) override;

    FORGE_API void onEnabled() override;

    FORGE_API void onDisabled() override;

	#pragma region Getters
    /// <summary>
    /// Acceso a la particula que esta siendo emitida
    /// </summary>
    /// <returns>El nombre de la particula en uso</returns>
    FORGE_API std::string const& getParticle() const;
    /// <summary>
    /// Acceso al estado de emision del sistema
    /// </summary>
    /// <returns>Estado de emision actual</returns>
    FORGE_API bool const& getEmitting() const;
	#pragma endregion

    #pragma region Setters
    /// <summary>
    /// Cambia la particula a emitir por el sistema
    /// </summary>
    /// <param name="newParticle">La nueva particula</param>
    FORGE_API void setParticle(std::string const& newParticle);
    /// <summary>
    /// Cambia el estado de emision del sistema de particulas
    /// </summary>
    /// <param name="newEmitting">Estado nuevo de emision</param>
    FORGE_API void setEmitting(bool newEmitting);
    #pragma endregion
};

#endif // !PARTICLESYSTEM_H_