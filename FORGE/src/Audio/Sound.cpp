#include "Sound.h"
#include <irrKlang.h>
#include "Vector3.h"

using namespace irrklang;
using namespace forge;

Sound::Sound(irrklang::ISoundEngine& _engine, irrklang::ISoundSource* _source) :
	engine(_engine),
	sound(nullptr),
	source(_source),
	loop(false) {
}

Sound::~Sound() {
	stop();
}

bool Sound::pause() {
	if (sound != nullptr && !sound->getIsPaused()) {
		sound->setIsPaused(true);
		return true;
	}
	return false;
}

bool Sound::resume() {
	if (sound != nullptr && sound->getIsPaused()) {
		sound->setIsPaused(false);
		return true;
	}
	return false;
}

bool Sound::stop() {
	if (sound != nullptr) {
		sound->stop();
		sound->drop();
		sound = nullptr;
		return true;
	}
	return false;
}

bool Sound::play() {
	if (sound == nullptr) {
		sound = engine.play2D(source, loop, false, true);
		return true;
	}
	return false;
}
bool Sound::play(Vector3 const& position) {
	if (sound == nullptr) {
		sound = engine.play3D(source, position, loop, false, true);
		return true;
	}
	return false;
}

void Sound::update() {
	if (sound != nullptr && sound->isFinished()) {
		stop();
	}
}

bool Sound::restart() {
	bool result;
	result = stop();
	result = play() || result;
	return result;
}

bool Sound::restart(forge::Vector3 const& position) {
	bool result;
	result = stop();
	if (result) {
		result = play(position);
	}
	return result;
}

void Sound::setVolume(float volume) {
	source->setDefaultVolume(volume);
	if (sound != nullptr) {
		sound->setVolume(volume);
	}
}

void Sound::loopedToggle() {
	loop = !loop;
	if (sound != nullptr) {
		sound->setIsLooped(loop);
	}
}

void Sound::setLooped(bool looped) {
	loop = looped;
	if (sound != nullptr) {
		sound->setIsLooped(loop);
	}
}

bool Sound::isFinished() {
	return sound == nullptr;
}

bool Sound::setPosition(forge::Vector3 const& position) {
	if (sound != nullptr) {
		sound->setPosition(position);
		return true;
	}
	return false;
}
