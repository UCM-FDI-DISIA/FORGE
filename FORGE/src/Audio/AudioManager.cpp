#include "AudioManager.h"
#include "Sound.h"
#include <irrKlang.h>
using namespace irrklang;

AudioManager::AudioManager() :
	engine(createIrrKlangDevice()) {
}

AudioManager::~AudioManager() {
	for (auto& s : soundLibrary) {
		delete s.second;
	}
	engine->drop();
}

void AudioManager::update() {

}

Sound* AudioManager::addSound(std::string name, std::string file) {
	ISoundSource* newSound = engine->addSoundSourceFromFile(file.c_str(), ESM_AUTO_DETECT , true);
	if (newSound != NULL) {
		Sound* s = new Sound(*engine, newSound, currentlyPlaying);
		soundLibrary.insert(std::pair<std::string, Sound*>(name, s)).second;
		return s;
	}
	return nullptr;
}

Sound* AudioManager::getSound(std::string name) {
	auto s = soundLibrary.find(name);
	if (s != soundLibrary.end()) {
		return s->second;
	}
	return nullptr;
}
