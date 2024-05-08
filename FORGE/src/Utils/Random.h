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
		static std::unique_ptr<Random> instance;
		std::random_device rd;
		std::mt19937 gen;

		Random();

		public:
		Random(Random const&) = delete;
		void operator=(Random const&) = delete;
		~Random();
		FORGE_API static Random* GetInstance();
		#pragma region Numeros aleatorios
		/// <summary>
		/// Genera un numero aleatorio en el intervalo: (0,t)
		/// </summary>
		/// <param name="t">Limite superior del intervalo</param>
		/// <returns>Numero aleatorio (float)</returns>
		FORGE_API float generate(float t);
		/// <summary>
		/// Genera un numero aleatorio en el intervalo (0,t)
		/// </summary>
		/// <param name="t">Limite superior del intervalo</param>
		/// <returns>Numero aleatorio (int)</returns>
		FORGE_API int generate(int t);
		/// <summary>
		/// Genera un numero aleatorio en el intervalo (a,b)
		/// </summary>
		/// <param name="a">Limite inferior del intervalo</param>
		/// <param name="b">Limite superior del intervalo</param>
		/// <returns>Numero aleatorio (float)</returns>
		FORGE_API float generateRange(float a, float b);
		/// <summary>
		/// Genera un numero aleatorio en el intervalo (a,b)
		/// </summary>
		/// <param name="a">Limite inferior del intervalo</param>
		/// <param name="b">Limite superior del intervalo</param>
		/// <returns>Numero aleatorio (int)</returns>
		FORGE_API int generateRange(int a, int b);
		#pragma endregion

		#pragma region Estructuras de FORGE aleatorias
		/// <summary>
		/// Genera un Vector3 aleatorio con valores normalizados
		/// </summary>
		/// <returns>Vector3 normalizado</returns>
		FORGE_API Vector3 getRandomVector();
		/// <summary>
		///  Genera un Quaternion aleatorio con valores normalizados
		/// </summary>
		/// <returns>Quaternion</returns>
		FORGE_API Quaternion getRandomQuaternion();
		#pragma endregion
	};
}
#endif