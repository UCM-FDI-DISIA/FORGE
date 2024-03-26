#pragma once
#ifndef RANDOM_H_
#define RANDOM_H_
#include <random>
#include "Vector2.h"
#include "Vector3.h"
#include "Quaternion.h"

namespace forge {
	class Random {
		public:
			Random() {}
			~Random() {}
			float generate(double t);
			int generate(int t);
			float generateRange(float inicio, float final);
			int generateRange(int inicio, int final);
			Vector3 getRandomVector();
			Quaternion getRandomQuaternion();

		private:

			std::random_device rd{};
			std::mt19937 gen{ rd() };

			std::uniform_real_distribution<float> uni{ -1.0,1.0 };
	};
}
#endif