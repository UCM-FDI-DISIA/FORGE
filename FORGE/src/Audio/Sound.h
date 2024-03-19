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
	bool play(bool looped = false);
	bool play(forge::Vector3 const& position, bool looped = false);
	bool update();
	bool restart();
	bool restart(forge::Vector3 const& position);
	void setVolume(float volume);
	void loopedToggle();
	void setLooped(bool looped);
	bool isFinished();
};

#endif