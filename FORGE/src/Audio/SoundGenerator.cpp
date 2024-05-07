#include "SoundGenerator.h"
#include <irrKlang.h>
#include "Sound.h"

using namespace irrklang;

SoundGenerator::SoundGenerator(ISoundEngine& _engine, ISoundSource* _source) :
	engine(_engine),
	source(_source) {
}

SoundGenerator::~SoundGenerator() {
	engine.removeSoundSource(source);
}

Sound* SoundGenerator::instanciate() {
	return new Sound(engine, *source);
}
