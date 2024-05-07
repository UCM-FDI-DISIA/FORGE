#include "AudioManager.h"
#include <iostream>
#include <irrKlang.h>
#include "Sound.h"
#include "SoundGenerator.h"
#include "ForgeError.h"
using namespace irrklang;
using namespace forge;

std::unique_ptr<AudioManager> AudioManager::instance = nullptr;

bool AudioManager::initialized = false;

AudioManager::AudioManager() :
	engine(createIrrKlangDevice()),
	currentListener(nullptr) {
}

bool AudioManager::Init() {
	instance = std::unique_ptr<AudioManager>(new AudioManager());
	if (instance.get()->engine != NULL) {
		initialized = true;
		return true;
	}
	throwError(false, "No se pudo crear el dispositivo de irrKlang");
}

AudioManager* AudioManager::GetInstance() {
	if (initialized) return instance.get();
	throwError(nullptr, "No se ha inicializado el AudioManager");
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

SoundGenerator* AudioManager::addSound(std::string const& name, std::string const& file) {
	ISoundSource* newSound = engine->addSoundSourceFromFile(file.c_str(), ESM_AUTO_DETECT , true);
	if (newSound == NULL) {
		throwError(nullptr, "Ya existia el audio \"" << file << "\"");
	}
	SoundGenerator* s = new SoundGenerator(*engine, newSound);
	soundLibrary.insert(std::pair<std::string, SoundGenerator*>(name, s)).second;
	return s;
}

Sound* AudioManager::getSound(std::string const& name) {
	auto s = soundLibrary.find(name);
	if (s == soundLibrary.end()) {
		throwError(nullptr, "No se registro ningun audio con el nombre indicado");
	}
	Sound* snd = s->second->instanciate();
	currentSounds.insert(snd);
	return snd;
}

bool AudioManager::removeSound(Sound* sound) {
	bool res = currentSounds.erase(sound);
	if (res) {
		delete sound;
	}
	return res;
}

void AudioManager::setListenerPosition(Vector3 const& position, Vector3 const& lookAt) {
	engine->setListenerPosition(position, lookAt, Vector3::ZERO, Vector3::UP);
}

bool AudioManager::registerListener(AudioListener* listener) {
	if (currentListener != nullptr) {
		return false;
	}
	currentListener = listener;
	return true;
}

bool AudioManager::deregisterListener(AudioListener* listener) {
	if (currentListener != listener) {
		return false;
	}
	currentListener = nullptr;
	return true;
}