#include "Audio.h"

Audio::Audio() {
	engine = createIrrKlangDevice();
}

Audio::~Audio() {
	for (auto s = soundLibrary.begin(); s != soundLibrary.end(); s++) {
		s->second->drop();
	}
	engine->drop();
}

void Audio::AddSound(char* name, char* file) {
	ISoundSource* newSound = engine->addSoundSourceFromFile(file);

	soundLibrary.insert(std::pair<char*, ISoundSource*>(name, newSound));
}

bool Audio::RemoveSound(char* name) {
	bool result = soundLibrary[name]->drop();
	soundLibrary.erase(name);
	return result;
}

void Audio::PlayGlobalSound(char* name, bool loop) {
	engine->play2D(soundLibrary[name], loop);
}

void Audio::SetSoundVolume(char* name, float volume) {
	soundLibrary[name]->setDefaultVolume(volume);
}