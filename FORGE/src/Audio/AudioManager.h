#pragma once
#ifndef AUDIO_H_
#define AUDIO_H_

#include <string>
#include <unordered_map>
#include <unordered_set>

namespace irrklang {
	class ISoundEngine;
	class ISoundSource;
	class ISound;
}

class Sound;
class SoundGenerator;

class AudioManager {
private:
	irrklang::ISoundEngine* engine;
	std::unordered_map<std::string, SoundGenerator*> soundLibrary;
	std::unordered_set<Sound*> currentSounds;
public:
	/// <summary>
	/// Inicializa el sistema de audio
	/// </summary>
	AudioManager();
	/// <summary>
	/// Cierra el sistema de audio
	/// </summary>
	~AudioManager();
	void update();
	/// <summary>
	/// Anade un sonido a la libreria de sonidos de audio
	/// </summary>
	/// <param name="name">Identificador del sonido</param>
	/// <param name="route">Archivo de sonido</param>
	/// <returns>Booleano que indica si se ha podido agregar el sonido</returns>
	SoundGenerator* addSound(std::string name, std::string file);
	/// <summary>
	/// Accede al sonido con el identificador solicitado
	/// </summary>
	/// <param name="name">Identificador del sonido al que se quiere acceder</param>
	/// <returns>Puntero al sonido solicitado. nullptr si no existe</returns>
	Sound* getSound(std::string name);
	/// <summary>
	/// Elimina el sonido de los sonidos actuales y lo borra de memoria
	/// </summary>
	/// <param name="sound">Puntero del sonido a eliminar</param>
	/// <returns>Si se ha encontrado el sonido a eliminar y se ha eliminado</returns>
	bool removeSound(Sound* sound);
};

#endif