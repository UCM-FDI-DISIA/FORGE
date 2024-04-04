#pragma once
#ifndef AUDIO_SOURCE_H_
#define AUDIO_SOURCE_H_
#include "Component.h"
#include "Vector3.h"
class Sound;
class Transform;
class AudioManager;
class __declspec(dllexport) AudioSource : public Component {
private:
	AudioManager& manager;
	Transform* transform;
	Sound* sound;
	
	bool playOnAwake;
	float fullVolumeRadious;
	float hearingRadious;
	forge::Vector3 offset;

	bool resumeOnEnable;

	static const std::string id;
public:
	static std::string const& Id();
	/// <summary>
	/// Constructora por defecto del component AudioSource
	/// </summary>
	AudioSource();
	/// <summary>
	/// Elimina su sonido del gestor
	/// </summary>
	~AudioSource() override;
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
	/// Reanuda la reproduccion del sonido si se estaba reproduciendo cuando se desactivo el componente
	/// </summary>
	void onEnabled() override;
	/// <summary>
	/// Pausa la reproduccion del sonido
	/// </summary>
	void onDisabled() override;
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
	/// Devuelve si la reproduccion del sonido esta en pausa
	/// </summary>
	/// <returns>Booleano que indica si la reproduccion esta en pausa</returns>
	bool isPaused();
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
	/// Devuelve el volumen con el que se reproduce el sonido
	/// </summary>
	/// <returns>Valor entre 0 y 1</returns>
	void getVolume() const;
	/// <summary>
	/// Establece el valor del paneo
	/// </summary>
	/// <param name="pan">Valor del paneo entre -1 y 1</param>
	void setPan(float pan);
	/// <summary>
	/// Devuelve el valor del paneo
	/// </summary>
	/// <returns>Valor del paneo actual entre -1 y 1</returns>
	void getPan() const;
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
	/// Devuelve el estado de bucle del sonido
	/// </summary>
	/// <returns>Booleano que indica que el audio esta en bucle o no</returns>
	bool isLooped() const;
	/// <summary>
	/// Comprueba si el sonido se esta reproduciendo
	/// </summary>
	/// <returns>Si el sonido se esta reproduciendo</returns>
	bool isPlaying() const;
	/// <summary>
	/// Establece el radio alrededor del objeto desde el que se escuchara el sonido con su maximo volumen
	/// </summary>
	/// <param name="value">Nuevo radio de escucha a maximo volumen</param>
	void setFullVolumeRadious(float value);
	/// <summary>
	/// Devuelve el valor del radio alrededor del objeto desde el que se escuchara el sonido con su maximo volumen
	/// </summary>
	/// <returns>El radio de escucha a maximo volumen</returns>
	float getFullVolumeRadious() const;
	/// <summary>
	/// Establece el radio alrededor del objeto a partir del que se empieza a escuchar
	/// </summary>
	/// <param name="value">El nuevo radio dentro del que se escucha el sonido</param>
	void setHearingRadious(float value);
	/// <summary>
	/// Devuelve el radio alrededor del objeto a partir del que se empieza a escuchar
	/// </summary>
	/// <returns>El radio dentro del que se escucha el sonido</returns>
	float getHearingRadious() const;
};
#endif // AUDIO_SOURCE_H_
