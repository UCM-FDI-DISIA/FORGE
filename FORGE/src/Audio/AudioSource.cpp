#include "AudioSource.h"
#include "ComponentData.h"
#include "Serializer.h"
#include "AudioManager.h"
#include "Transform.h"
#include "Entity.h"
#include "Sound.h"

const std::string AudioSource::id = "AudioSource";

AudioSource::AudioSource() :
	sound(nullptr),
	transform(nullptr),
	manager(*AudioManager::getInstance()),
	playOnAwake(false),
	offset(),
	fullVolumeRadious(5.0f),
	hearingRadious(50.0f),
	resumeOnEnable(false) {

	serializer(playOnAwake, "playOnAwake");
	serializer(offset, "offset");
}

AudioSource::~AudioSource() {
	manager.removeSound(sound);
}

void AudioSource::initComponent(ComponentData* data) {
	sound = manager.getSound(data->get<std::string>("sound"));
	transform = entity->getComponent<Transform>();
	if (data->has("volume")) {
		sound->setVolume(data->get<float>("volume"));
	}
	if (data->has("pan")) {
		sound->setPan(data->get<float>("pan"));
	}
	if (data->has("fullVolumeRadious")) {
		sound->setFullVolumeRadious(data->get<float>("fullVolumeRadious"));
	}
	if (data->has("hearingRadious")) {
		sound->setHearingRadious(data->get<float>("hearingRadious"));
	}
	if (playOnAwake) {
		play();
	}
}

void AudioSource::update() {
	if (transform != nullptr && transform->getNeedsUpdate()) {
		sound->setPosition(transform->getGlobalPosition());
	}
}

void AudioSource::onEnabled() {
	if (resumeOnEnable) {
		resumeOnEnable = false;
		resume();
	}
}

void AudioSource::onDisabled() {
	if (isPlaying() && !isPaused()) {
		resumeOnEnable = true;
		pause();
	}
}

bool AudioSource::pause() {
	return sound->pause();
}

bool AudioSource::resume() {
	return sound->resume();
}

bool AudioSource::isPaused() {
	return sound->isPaused();
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

void AudioSource::getVolume() const {
	sound->getVolume();
}

void AudioSource::setPan(float pan) {
	sound->setPan(pan);
}

void AudioSource::getPan() const {
	sound->getPan();
}

void AudioSource::loopedToggle() {
	sound->loopedToggle();
}

void AudioSource::setLooped(bool looped) {
	sound->setLooped(looped);
}

bool AudioSource::isLooped() const {
	return sound->isLooped();
}

bool AudioSource::isPlaying() const {
	return !sound->isFinished();
}

void AudioSource::setFullVolumeRadious(float value) {
	sound->setFullVolumeRadious(value);
}
float AudioSource::getFullVolumeRadious() const {
	return sound->getFullVolumeRadious();
}
void AudioSource::setHearingRadious(float value) {
	sound->setHearingRadious(value);
}
float AudioSource::getHearingRadious() const {
	return sound->getHearingRadious();
}