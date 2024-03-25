#pragma once
#ifndef AUDIO_SOURCE_H_
#define AUDIO_SOURCE_H_
#include "Component.h"
#include "Vector3.h"
class Sound;
class Transform;
class AudioManager;
class AudioSource : public Component {
private:
	AudioManager& manager;
	Transform* transform;
	Sound* sound;
	
	bool playOnAwake;
	float volume;
	float pan;
	float fullVolumeRadious;
	float hearingRadious;
	forge::Vector3 offset;

public:
	static const std::string id;
	/// <summary>
	/// Constructora por defecto del component AudioSource
	/// </summary>
	AudioSource();
	/// <summary>
	/// Se llama en la creacion del componente AudioSource
	/// </summary>
	/// <param name="data">Bloque con la informacion guardada para el componente</param>
	void initComponent(ComponentData* data) override;
	/// <summary>
	/// Actualiza la logica del componente, llamandose en cada iteracion del bucle principal
	/// </summary>
	void update() override;
	/// <summary>
	/// Pausa el sonido si esta sonando
	/// </summary>
	/// <returns>Si se ha podido pausar</returns>
	bool pause();
	/// <summary>
	/// Reanuda el sonido desde donde se habia pausado
	/// </summary>
	/// <returns>Si se ha podido reanudar</returns>
	bool resume();
	/// <summary>
	/// Detiene por completo el sonido
	/// </summary>
	/// <returns>Si se ha podido detener</returns>
	bool stop();
	/// <summary>
	/// Comienza a reproducir el sonido
	/// </summary>
	/// <returns>Si se ha podido reproducir</returns>
	bool play();
	/// <summary>
	/// Reinicia el sonido. Detiene el sonido y lo vuelve a reproducir desde el principio
	/// </summary>
	/// <returns>Si se ha podido reiniciar el sonido</returns>
	bool restart();
	/// <summary>
	/// Establece el volumen con el que se reproduce el sonido
	/// </summary>
	/// <param name="volume">Valor entre 0 y 1</param>
	void setVolume(float volume);
	/// <summary>
	/// Cambia el estado de bucle del sonido
	/// </summary>
	void loopedToggle();
	/// <summary>
	/// Establece el estado de bucle del sonido
	/// </summary>
	/// <param name="looped">Nuevo estado de bucle del sonido</param>
	void setLooped(bool looped);
	/// <summary>
	/// Comprueba si el sonido se esta reproduciendo
	/// </summary>
	/// <returns>Si el sonido se esta reproduciendo</returns>
	bool isPlaying();
};
#endif // AUDIO_SOURCE_H_
