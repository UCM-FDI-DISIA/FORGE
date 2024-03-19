#pragma once
#ifndef SOUND_H_
#define SOUND_H_

#include <string>
#include <unordered_map>
namespace irrklang {
	class ISoundEngine;
	class ISoundSource;
	class ISound;
}
namespace forge {
	class Vector3;
}
class Sound {
private:
	irrklang::ISoundEngine& engine;
	irrklang::ISoundSource* source;
	irrklang::ISound* sound;
	bool loop;
public:
	/// <summary>
	/// Crea una nueva instancia de Sound
	/// </summary>
	/// <param name="_engine">Engine de irrklang desde el que sonara el audio</param>
	/// <param name="_source">ISoundSource de irrklang con el sonido que sonara</param>
	Sound(irrklang::ISoundEngine& _engine, irrklang::ISoundSource* _source);
	/// <summary>
	/// Detiene el sonido y lo destruye
	/// </summary>
	~Sound();
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
	/// <param name="looped">Si se quiere reproducir en bucle</param>
	/// <returns>Si se ha podido reproducir</returns>
	bool play();
	/// <summary>
	/// Comienza a reproducir el sonido en un punto en concreto
	/// </summary>
	/// <param name="position">Posicion desde la que se quiere que se reproduzca</param>
	/// <param name="looped">Si se quiere reproducir en bucle</param>
	/// <returns>Si se ha podido reproducir</returns>
	bool play(forge::Vector3 const& position);
	/// <summary>
	/// Actualiza el estado del sonido segun se haya terminado o no de reproducir
	/// </summary>
	void update();
	/// <summary>
	/// Reinicia el sonido. Detiene el sonido y lo vuelve a reproducir desde el principio
	/// </summary>
	/// <returns>Si se ha podido reiniciar el sonido</returns>
	bool restart();
	/// <summary>
	/// Reinicia el sonido teniendo en cuenta la posicion. Detiene el sonido y lo vuelve a reproducir desde el principio en la posicion indicada
	/// </summary>
	/// <param name="position">Posicion desde la que se quiere que se reproduzca</param>
	/// <returns>Si se ha podido reiniciar el sonido</returns>
	bool restart(forge::Vector3 const& position);
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
	/// Comprueba si el sonido ha terminado de reproducirse
	/// </summary>
	/// <returns>Si el sonido ha terminado o se ha detenido</returns>
	bool isFinished();
	/// <summary>
	/// Establece la posicion desde la que se reproduce el sonido
	/// </summary>
	/// <param name="position">Posicion desde la que se reproducira el sonido</param>
	/// <returns>Si se ha podido establecer la posicion del sonido</returns>
	bool setPosition(forge::Vector3 const& position);
};

#endif