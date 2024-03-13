#include "AudioManager.h"
#include "Sound.h"
#include <irrKlang.h>
using namespace irrklang;

AudioManager::AudioManager() :
	engine(createIrrKlangDevice()) {
}

AudioManager::~AudioManager() {
	engine->drop();
}

bool AudioManager::AddSound(std::string name, std::string file) {
	ISoundSource* newSound = engine->addSoundSourceFromFile(file.c_str(), ESM_AUTO_DETECT , true);
	if (newSound != NULL) {
		soundLibrary.insert(std::pair<std::string, ISoundSource*>(name, newSound)).second;
		return true;
	}
	return false;
}

bool AudioManager::RemoveSound(std::string name) {
	auto sound = soundLibrary.find(name);
	if (sound != soundLibrary.end()) {
		engine->removeSoundSource(sound->second);
		soundLibrary.erase(sound);
		return true;
	}
	return false;
}

bool AudioManager::PlayGlobalSound(std::string name, bool loop) {
	auto sound = soundLibrary.find(name);
	if (sound != soundLibrary.end()) {
		engine->play2D(sound->second, loop);
		return true;
	}
	return false;
}

bool AudioManager::SetSoundVolume(std::string name, float volume) {
	auto sound = soundLibrary.find(name);
	if (sound != soundLibrary.end()) {
		sound->second->setDefaultVolume(volume);
		return true;
	}
	return false;
}