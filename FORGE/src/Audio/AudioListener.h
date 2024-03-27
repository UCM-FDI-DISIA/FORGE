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
    
public:
    static const std::string id;
    /// <summary>
    /// Crea el escuchador con valores por defecto
    /// </summary>
    AudioListener();
	/// <summary>
	/// Se inicializa el escuchador con el transform de la entidad
	/// </summary>
	/// <param name="data"></param>
	void initComponent(ComponentData* data) override;
	/// <summary>
	/// Comprueba si hay que actualizar la posicion del escuchador y si es asi
	/// la actualiza
	/// </summary>
	void update() override;
};
#endif // AUDIO_LISTENER_H_
