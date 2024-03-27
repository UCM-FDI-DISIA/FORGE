#pragma once
#ifndef SOUND_GENERATOR_H_
#define SOUND_GENERATOR_H_

#include <string>
#include <unordered_map>
namespace irrklang {
	class ISoundEngine;
	class ISoundSource;
	class ISound;
}
class Sound;
class SoundGenerator {
private:
	irrklang::ISoundEngine& engine;
	irrklang::ISoundSource* source;
public:
	/// <summary>
	/// Crea un SoundGenerator
	/// </summary>
	/// <param name="_engine">Engine de irrklang desde el que sonara el audio</param>
	/// <param name="_source">ISoundSource de irrklang con el sonido que sonara</param>
	SoundGenerator(irrklang::ISoundEngine& _engine, irrklang::ISoundSource* _source);
	/// <summary>
	/// Elimina el SoundSource de irrklang
	/// </summary>
	~SoundGenerator();
	/// <summary>
	/// Crea una nueva instancia de Sound con el sonido de este SoundGenerator
	/// </summary>
	/// <returns>Puntero a la nueva instancia de Sound</returns>
	Sound* instanciate();
};

#endif