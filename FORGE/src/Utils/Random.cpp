#include "Random.h"

using namespace forge;

float Random::generate(double t) {
	return abs(uni(rd) * t);
}

int forge::Random::generate(int t) {
	return abs(uni(rd) * t);
}

float forge::Random::generateRange(float inicio, float fin) {
	float diference = fin - inicio;
	return uni(rd)* diference + inicio;
}

int forge::Random::generateRange(int inicio, int fin) {
	int diference = fin - inicio;
	return uni(rd) * diference + inicio;
}

Vector3 Random::getRandomVector() {
	return Vector3(uni(rd), uni(rd), uni(rd)).normalized();
}

Quaternion forge::Random::getRandomQuaternion() {
	Vector3 v = Vector3(uni(rd), uni(rd), uni(rd)).normalized();
	return Quaternion(v.getX(), v.getY(), v.getZ(), generateRange(0.0f, 360.0f));
}