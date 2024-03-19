#include "AudioSource.h"
#include "AudioManager.h"
#include "ComponentData.h"
#include "Transform.h"
#include "Entity.h"
#include "Sound.h"
#include "Serializer.h"

const std::string AudioSource::id = "AudioSource";

AudioSource::AudioSource() :
	sound(nullptr),
	transform(nullptr),
	manager(*AudioManager::getInstance()),
	playOnAwake(false),
	offset(),
	maxVolumeRadious(0.0f),
	hearingRadious(0.0f),
	pan(0.0f),
	volume(1.0f) {

	serializer(playOnAwake, "playOnAwake");
	serializer(offset, "offset");
	serializer(maxVolumeRadious, "maxVolumeRadious");
	serializer(hearingRadious, "hearingRadious");
	serializer(pan, "pan");
	serializer(volume, "volume");
}

void AudioSource::initComponent(ComponentData* data) {
	sound = manager.getSound(data->get<std::string>("sound"));
	transform = entity->getComponent<Transform>();
	if (playOnAwake) {
		play();
	}
}

void AudioSource::update() {
	if (transform != nullptr && transform->getNeedsUpdate()) {
		sound->setPosition(transform->getGlobalPosition());
	}
}

bool AudioSource::pause() {
	return sound->pause();
}

bool AudioSource::resume() {
	return sound->resume();
}

bool AudioSource::stop() {
	return sound->stop();
}

bool AudioSource::play() {

	if (transform != nullptr) {
		return sound->play(transform->getGlobalPosition() + offset);
	}
	return sound->play();
}

bool AudioSource::restart() {
	bool res = stop();
	res = play() || res;
	return res;
}

void AudioSource::setVolume(float volume) {
	sound->setVolume(volume);
}

void AudioSource::loopedToggle() {
	sound->loopedToggle();
}

void AudioSource::setLooped(bool looped) {
	sound->setLooped(looped);
}

bool AudioSource::isPlaying() {
	return !sound->isFinished();
}
