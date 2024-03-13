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
	using SoundMap = std::unordered_multimap<irrklang::ISoundSource*, irrklang::ISound*>;
	SoundMap& sounds;
	SoundMap::iterator position;
	irrklang::ISoundSource* source;
	irrklang::ISound* sound;
	bool looped;
public:
	Sound(irrklang::ISoundEngine& _engine, SoundMap& _sounds, irrklang::ISoundSource* _source, bool loop);
	~Sound();
	void update();
	bool pause();
	bool resume();
	bool stop();
	bool play();
	bool play(forge::Vector3 const& position);
	bool restart();
	bool setVolume();
	bool loop();
	bool isFinished();
};

#endif