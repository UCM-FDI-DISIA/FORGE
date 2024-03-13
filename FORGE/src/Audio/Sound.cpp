#include "Sound.h"
#include <irrKlang.h>
#include "Vector3.h"
using namespace irrklang;
using namespace forge;




Sound::Sound(irrklang::ISoundEngine& _engine, SoundMap& _sounds, irrklang::ISoundSource* _source, bool _loop) :
	engine(_engine),
	sounds(_sounds),
	position(_sounds.end()),
	sound(nullptr),
	source(_source),
	looped(_loop) {
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

bool Sound::stop() {
	if (sound != nullptr) {
		sound->stop();
		sounds.erase(position);
		position = sounds.end();
		sound->drop();
		sound = nullptr;
		return true;
	}
	return false;
}

bool Sound::play() {
	if (sound == nullptr) {
		sound = engine.play2D(source, looped, false, true);
		return true;
	}
	return false;
}
bool Sound::play(Vector3 const& position) {
	if (sound == nullptr) {
		sound = engine.play3D(source, position, looped, false, true);
		return true;
	}
	return false;
}