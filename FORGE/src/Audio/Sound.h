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
	using Sounds = std::list<Sound*>;
	irrklang::ISoundEngine& engine;
	irrklang::ISoundSource* source;
	irrklang::ISound* sound;
	Sounds& currentlyPlaying;
	Sounds::iterator it;
	bool loop;
public:
	Sound(irrklang::ISoundEngine& _engine, irrklang::ISoundSource* _source, std::list<Sound*>& _currentlyPlaying);
	~Sound();
	bool pause();
	bool resume();
	bool stop();
	bool play(bool looped = false);
	bool play(forge::Vector3 const& position, bool looped = false);
	bool restart();
	bool restart(forge::Vector3 const& position);
	void setVolume(float volume);
	void loopedToggle();
	void setLooped(bool looped);
	bool isFinished();
};

#endif