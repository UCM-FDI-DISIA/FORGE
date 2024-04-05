#pragma once
#ifndef AUDIO_LISTENER_H_
#define AUDIO_LISTENER_H_
#include "Component.h"
class Transform;
class AudioManager;
class AudioListener : public Component {
private:
    Transform* transform;
    AudioManager& manager;
	bool isListenerActive = false;
public:
	static const FORGE_API_VAR std::string id;
    /// <summary>
    /// Crea el escuchador con valores por defecto
    /// </summary>
	FORGE_API AudioListener();
	/// <summary>
	/// Destructora de audio listener, si es el listener activo
	/// hace que el manager cambie la flag de listener activo a falso
	/// </summary>
	FORGE_API ~AudioListener() override;
	/// <summary>
	/// Se inicializa el escuchador con el transform de la entidad
	/// </summary>
	/// <param name="data"></param>
	FORGE_API void initComponent(ComponentData* data) override;
	/// <summary>
	/// Comprueba si hay que actualizar la posicion del escuchador y si es asi
	/// la actualiza
	/// </summary>
	FORGE_API void update() override;
};
#endif // AUDIO_LISTENER_H_
