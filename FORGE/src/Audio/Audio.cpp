#include "Audio.h"
#include <irrKlang.h>
using namespace irrklang;

Audio::Audio() :
	engine(createIrrKlangDevice()) {
}

Audio::~Audio() {
	//for (auto& s : soundLibrary) {
	//	s.second->drop();
	//}
	engine->drop();
}

bool Audio::AddSound(std::string name, std::string file) {
	ISoundSource* newSound = engine->addSoundSourceFromFile(file.c_str());
	if (newSound != NULL) {
		soundLibrary.insert(std::pair<std::string, ISoundSource*>(name, newSound)).second;
		return true;
	}
	return false;
}

bool Audio::RemoveSound(std::string name) {
	auto sound = soundLibrary.find(name);
	if (sound != soundLibrary.end()) {
		engine->removeSoundSource(sound->second);
		soundLibrary.erase(sound);
		return true;
	}
	return false;
}

bool Audio::PlayGlobalSound(std::string name, bool loop) {
	auto sound = soundLibrary.find(name);
	if (sound != soundLibrary.end()) {
		engine->play2D(sound->second, loop);
		return true;
	}
	return false;
}

bool Audio::SetSoundVolume(std::string name, float volume) {
	auto sound = soundLibrary.find(name);
	if (sound != soundLibrary.end()) {
		sound->second->setDefaultVolume(volume);
		return true;
	}
	return false;
}