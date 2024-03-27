#pragma once
#ifndef RANDOM_H_
#define RANDOM_H_
#include <random>
#include <memory>
#include "Vector2.h"
#include "Vector3.h"
#include "Quaternion.h"

namespace forge {
	class Random {
		private:
		//static std::unique_ptr<Random> instance;
		std::random_device rd;
		std::mt19937 gen;

		public:
		Random();
		~Random();
		//static Random* getInstance();
		float generate(double t);
		int generate(int t);
		float generateRange(float inicio, float final);
		int generateRange(int inicio, int final);
		Vector3 getRandomVector();
		Quaternion getRandomQuaternion();

	};
}
#endif