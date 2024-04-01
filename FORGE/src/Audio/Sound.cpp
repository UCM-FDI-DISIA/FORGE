#include "Sound.h"
#include <irrKlang.h>
#include "Vector3.h"

using namespace irrklang;
using namespace forge;

Sound::Sound(ISoundEngine& _engine, ISoundSource* _source) :
	engine(_engine),
	sound(nullptr),
	source(_source),
	loop(false),
	pan(0.0f),
	fullVolumeRadious(20.0f),
	hearingRadious(200.0f) {
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

bool Sound::isPaused() {
	return sound != nullptr && sound->getIsPaused();
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
		sound->setMinDistance(fullVolumeRadious);
		sound->setMaxDistance(hearingRadious);
		sound->setPan(pan);
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

float Sound::getVolume() const {
	return sound->getVolume();
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

bool Sound::isLooped() const {
	return loop;
}

void Sound::setPan(float value) {
	pan = value;
	if (sound != nullptr) {
		sound->setPan(pan);
	}
}

float Sound::getPan() const {
	return pan;
}

bool Sound::isFinished() const {
	return sound == nullptr;
}

bool Sound::setPosition(forge::Vector3 const& position) {
	if (sound != nullptr) {
		sound->setPosition(position);
		return true;
	}
	return false;
}

void Sound::setFullVolumeRadious(float value) {
	fullVolumeRadious = value;
	if (sound != nullptr) {
		sound->setMinDistance(value);
	}
}

float Sound::getFullVolumeRadious() const {
	return fullVolumeRadious;
}

void Sound::setHearingRadious(float value) {
	hearingRadious = value;
	if (sound != nullptr) {
		sound->setMaxDistance(value);
	}
}

float Sound::getHearingRadious() const {
	return hearingRadious;
}