#include "Sound.h"
#include <irrKlang.h>
#include <ik_vec3d.h>
#include "AudioManager.h"
#include "Vector3.h"
#include "ForgeError.h"

using namespace irrklang;
using namespace forge;

Sound::Sound(ISoundEngine& _engine, ISoundSource& _source) :
	manager(*AudioManager::GetInstance()),
	engine(_engine),
	sound(nullptr),
	source(_source),
	loop(false),
	pan(0.0f),
	volume(1.0f),
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
		sound = engine.play2D(&source, loop, false, true);
		if (sound == NULL) {
			sound = nullptr;
			throwError(false, "No se pudo reproducir el audio 2D");
		}
		sound->setVolume(volume);
		sound->setPan(pan);
		return true;
	}
	return false;
}
bool Sound::play(Vector3 const& position) {
	if (sound == nullptr) {
		sound = engine.play3D(&source, manager.forgeVector3ToIrrklangVec3(position), loop, false, true);
		if (sound == NULL) {
			sound = nullptr;
			throwError(false, "No se pudo reproducir el audio 3D");
		}
		sound->setMinDistance(fullVolumeRadious);
		sound->setMaxDistance(hearingRadious);
		sound->setVolume(volume);
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
	result = play(position) || result;
	return result;
}

void Sound::setVolume(float value) {
	volume = value;
	if (sound != nullptr) {
		sound->setVolume(volume);
	}
}

float Sound::getVolume() const {
	return volume;
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
		sound->setPosition(manager.forgeVector3ToIrrklangVec3(position));
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