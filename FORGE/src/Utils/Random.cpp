#include "Random.h"

using namespace forge;

#pragma region Constructores
std::unique_ptr<Random> Random::instance = nullptr;

Random::Random() : gen(rd()) {}

Random::~Random() {

}

Random* Random::GetInstance() {
	if (instance != nullptr) return instance.get();
	return (instance = std::unique_ptr<Random>(new Random())).get();
}
#pragma endregion

#pragma region Numeros aleatorios
float Random::generate(float t) {
	std::uniform_real_distribution<float> uni(0.0f, t);
	return uni(gen);
}

int forge::Random::generate(int t) {
	std::uniform_int_distribution<int> uni(0, t);
	return uni(gen);
}

float forge::Random::generateRange(float a, float b) {
	std::uniform_real_distribution<float> uni(a, b);
	return uni(gen);
}

int forge::Random::generateRange(int a, int b) {
	std::uniform_int_distribution<int> uni(a, b);
	return uni(gen);
}
#pragma endregion

#pragma region Estructuras de FORGE aleatorias
Vector3 Random::getRandomVector() {
	std::uniform_real_distribution<float> uni(-1, 1);
	return Vector3(uni(gen), uni(gen), uni(gen));
}

Quaternion forge::Random::getRandomQuaternion() {
	return Quaternion(getRandomVector(), generateRange(0.0f, 360.0f));
}
#pragma endregion