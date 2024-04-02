#include "SoundGenerator.h"
#include <irrKlang.h>
#include "Sound.h"

using namespace irrklang;
using namespace forge;

SoundGenerator::SoundGenerator(irrklang::ISoundEngine& _engine, irrklang::ISoundSource* _source) :
	engine(_engine),
	source(_source) {
}

SoundGenerator::~SoundGenerator() {
	engine.removeSoundSource(source);
}

Sound* SoundGenerator::instanciate() {
	return new Sound(engine, source);
}
