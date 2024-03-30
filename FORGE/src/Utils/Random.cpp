#include "Random.h"

using namespace forge;

Random::Random() : gen(rd()) {
}

Random::~Random() {

}

// Random* Random::getInstance() {
// 	if (instance.get() != nullptr) return instance.get();
// 	return (instance = std::unique_ptr<Random>(new Random())).get();
// }

float Random::generate(float t) {
	std::uniform_real_distribution<float> uni(0,t);
	return uni(gen);
}

int forge::Random::generate(int t) {
	std::uniform_int_distribution<int> uni(0, t);
	return uni(gen);
}

float forge::Random::generateRange(float inicio, float fin) {
	std::uniform_real_distribution<float> uni(inicio, fin);
	return uni(gen);
}

int forge::Random::generateRange(int inicio, int fin) {
	std::uniform_int_distribution<int> uni(inicio, fin);
	return uni(gen);
}

Vector3 Random::getRandomVector() {
	std::uniform_real_distribution<float> uni(-1,1);
	return Vector3(uni(gen), uni(gen), uni(gen));
}

Quaternion forge::Random::getRandomQuaternion() {
	std::uniform_real_distribution<float> uni(-1, 1);
	return Quaternion(uni(gen), uni(gen), uni(gen), generateRange(0.0f, 360.0f));
}