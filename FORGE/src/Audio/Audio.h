#pragma once
#ifndef AUDIO_H_
#define AUDIO_H_

#include "irrKlang.h"
#include "unordered_map"
using namespace irrklang;

class Audio {
private:
	ISoundEngine* engine;
	std::unordered_map<char*, ISoundSource*> soundLibrary;
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
	void AddSound(char* name, char* file);
	/// <summary>
	/// Elimina un sonido de la libreria de sonidos de audio
	/// </summary>
	/// <param name="name">Identificador del sonido</param>
	/// <returns>Booleano con el resultado de la operación</returns>
	bool RemoveSound(char* name);
	/// <summary>
	/// Hace sonar un sonido de forma global sin tener en cuenta posiciones
	/// </summary>
	/// <param name="name">Identificador del sonido</param>
	/// <param name="loop">Booleano de control de loop</param>
	void PlayGlobalSound(char* name, bool loop);
	/// <summary>
	/// Pone un sonido al volumen especificado
	/// </summary>
	/// <param name="name">Identificador del sonido</param>
	/// <param name="volume">Volumen del sonido, va del 0 al 1f</param>
	void SetSoundVolume(char* name, float volume);
};

#endif