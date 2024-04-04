#include "AudioManager.h"
#include <irrKlang.h>
#include "Sound.h"
#include "SoundGenerator.h"
using namespace irrklang;

std::unique_ptr<AudioManager> AudioManager::instance = nullptr;

AudioManager::AudioManager() :
	engine(createIrrKlangDevice()),
	isListenerOnScene(false) {
}

AudioManager* AudioManager::getInstance() {
	if (instance.get() != nullptr) return instance.get();
	return (instance = std::unique_ptr<AudioManager>(new AudioManager())).get();
}

AudioManager::~AudioManager() {
	for (auto& s : currentSounds) {
		delete s;
	}
	for (auto& s : soundLibrary) {
		delete s.second;
	}
	engine->drop();
}

void AudioManager::update() {
	for (auto& s : currentSounds) {
		s->update();
	}
}

SoundGenerator* AudioManager::addSound(std::string name, std::string file) {
	ISoundSource* newSound = engine->addSoundSourceFromFile(file.c_str(), ESM_AUTO_DETECT , true);
	if (newSound != NULL) {
		SoundGenerator* s = new SoundGenerator(*engine, newSound);
		soundLibrary.insert(std::pair<std::string, SoundGenerator*>(name, s)).second;
		return s;
	}
	return nullptr;
}

Sound* AudioManager::getSound(std::string name) {
	auto s = soundLibrary.find(name);
	if (s != soundLibrary.end()) {
		Sound* snd = s->second->instanciate();
		currentSounds.insert(snd);
		return snd;
	}
	return nullptr;
}

bool AudioManager::removeSound(Sound* sound) {
	bool res = currentSounds.erase(sound);
	if (res) {
		delete sound;
	}
	return res;
}

using namespace forge;
void AudioManager::setListenerPosition(Vector3 position, Vector3 lookAt) {
	engine->setListenerPosition(position, lookAt, Vector3::ZERO, Vector3::UP);
}

bool AudioManager::getListenerOnScene() {
	return isListenerOnScene;
}

void AudioManager::registerListenerOnScene() {
	isListenerOnScene = true;
}

void AudioManager::clearListenerOnScene() {
	isListenerOnScene = false;
}