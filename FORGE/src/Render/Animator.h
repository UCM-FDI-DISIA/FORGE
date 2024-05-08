#pragma once
#ifndef ANIMATOR_H_
#define ANIMATOR_H_
#include "Mesh.h"
#include <unordered_set>

namespace Ogre {
    class AnimationStateSet;
}

class Animator : public Mesh {
    std::unordered_set<std::string> activeAnimations;
    Ogre::AnimationStateSet* ogreAnimations;

public:
    static const FORGE_API_VAR std::string id;

    /// <summary>
    /// Crea el Animator con valores por defecto
    /// </summary>
    FORGE_API Animator();

    /// <summary>
    /// Obtiene los datos de todas las animaciones asociadas a la malla
    /// y establece como activas las indicadas en el archivo lua
    /// </summary>
    /// <param name="data">Data con los datos del mesh y las animaciones</param>
    FORGE_API bool initComponent(ComponentData* data) override;
    /// <summary>
    /// Obtiene los datos de todas las animaciones asociadas a la malla
    /// </summary>
    FORGE_API void onEnabled() override;
    /// <summary>
    /// Actualiza las animaciones activas agregandole el tiempo transcurrido
    /// </summary>
    FORGE_API void update() override;

    #pragma region Getters
    /// <summary>
    /// Devuelve todos nombres de las animaciones asociadas a la malla
    /// </summary>
    /// <returns>Un vector con todos los nombres de las animaciones asociadas a la malla</returns>
    FORGE_API std::vector<std::string> getAnimations() const;
    /// <summary>
    /// Devuelve todos nombres de las animaciones activas
    /// </summary>
    /// <returns>Un unordered set con todos los nombres de las animaciones activas</returns>
    FORGE_API std::unordered_set<std::string> const& getActiveAnimations() const;
    #pragma endregion

    #pragma region Setters
    /// <summary>
    /// Establece el estado de bucle de una animacion
    /// </summary>
    /// <param name="animation">Nombre de la animacion modificada</param>
    /// <param name="looped">Nuevo estado de bucle</param>
    FORGE_API void setLoop(std::string const& animation, bool looped);
    /// <summary>
    /// Establece el estado de reproduccion de una animacion
    /// </summary>
    /// <param name="animation">Nombre de la animacion modificada</param>
    /// <param name="active">Nuevo estado de bucle</param>
    FORGE_API void setActive(std::string const& animation, bool active);
    /// <summary>
    /// Establece el estado de bucle de varias animaciones
    /// </summary>
    /// <param name="animations">Vector con los nombres de las animaciones modificadas</param>
    /// <param name="looped">Nuevo estado de bucle de las animaciones</param>
    FORGE_API void setLoop(std::vector<std::string> const& animations, bool looped);
    /// <summary>
    /// Establece el estado de reproduccion de varias animaciones
    /// </summary>
    /// <param name="animations">Vector con los nombres de las animaciones modificadas</param>
    /// <param name="active">Nuevo estado de reproduccion de las animaciones</param>
    FORGE_API void setActive(std::vector<std::string> const& activeAnimations, bool active);
    /// <summary>
    /// Establece el estado de una unica animacion a verdadero
    /// y el de todas las demas a falso 
    /// </summary>
    /// <param name="animation">Nombre de las animacion que se reproducira</param>
    FORGE_API void changeActive(std::string const& animation);
    /// <summary>
    /// Establece el estado de un conjunto de animaciones a verdadero
    /// y el de todas las demas a falso 
    /// </summary>
    /// <param name="activeAnimations">Vector con los nombres de las animaciones que se reproduciran</param>
    FORGE_API void changeActive(std::vector<std::string> const& activeAnimations);
    #pragma endregion
};

#endif // !ANIMATOR_H_