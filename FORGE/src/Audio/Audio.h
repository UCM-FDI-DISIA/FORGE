#pragma once
#ifndef AUDIO_H_
#define AUDIO_H_

#include <string>
#include <unordered_map>
namespace irrklang {
	class ISoundEngine;
	class ISoundSource;
}
class Audio {
private:
	irrklang::ISoundEngine* engine;
	std::unordered_map<std::string, irrklang::ISoundSource*> soundLibrary;
public:
	/// <summary>
	/// Inicializa el sistema de audio
	/// </summary>
	Audio();
	/// <summary>
	/// Cierra el sistema de audio
	/// </summary>
	~Audio();
	/// <summary>
	/// Anade un sonido a la libreria de sonidos de audio
	/// </summary>
	/// <param name="name">Identificador del sonido</param>
	/// <param name="route">Archivo de sonido</param>
	/// <returns>Booleano que indica si se ha podido agregar el sonido</returns>
	bool AddSound(std::string name, std::string file);
	/// <summary>
	/// Elimina un sonido de la libreria de sonidos de audio
	/// </summary>
	/// <param name="name">Identificador del sonido</param>
	/// <returns>Booleano que indica si se encontro y elimino el sonido</returns>
	bool RemoveSound(std::string name);
	/// <summary>
	/// Hace sonar un sonido de forma global sin tener en cuenta posiciones
	/// </summary>
	/// <param name="name">Identificador del sonido</param>
	/// <param name="loop">Booleano de control de loop</param>
	/// <returns>Booleano que indica si se ha encontrado el sonido y se ha reproducido</returns>
	bool PlayGlobalSound(std::string name, bool loop);
	/// <summary>
	/// Pone un sonido al volumen especificado
	/// </summary>
	/// <param name="name">Identificador del sonido</param>
	/// <param name="volume">Volumen del sonido, va del 0 al 1f</param>
	/// <returns>Booleano que indica si se ha encontrado el sonido y cambiado su volumen</returns>
	bool SetSoundVolume(std::string name, float volume);
};

#endif