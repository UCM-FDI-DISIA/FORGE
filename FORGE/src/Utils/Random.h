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

		public:
		#pragma region Constructores
		Random();
		~Random();
		static Random* getInstance();
		#pragma region Numeros aleatorios
		/// <summary>
		/// Genera un numero aleatorio en el intervalo: (0,t)
		/// </summary>
		/// <param name="t">Limite superior del intervalo</param>
		/// <returns>Numero aleatorio (float)</returns>
		float generate(double t);
		/// <summary>
		/// Genera un numero aleatorio en el intervalo (0,t)
		/// </summary>
		/// <param name="t">Limite superior del intervalo</param>
		/// <returns>Numero aleatorio (int)</returns>
		int generate(int t);
		/// <summary>
		/// Genera un numero aleatorio en el intervalo (a,b)
		/// </summary>
		/// <param name="a">Limite inferior del intervalo</param>
		/// <param name="b">Limite superior del intervalo</param>
		/// <returns>Numero aleatorio (float)</returns>
		float generateRange(float a, float b);
		/// <summary>
		/// Genera un numero aleatorio en el intervalo (a,b)
		/// </summary>
		/// <param name="a">Limite inferior del intervalo</param>
		/// <param name="b">Limite superior del intervalo</param>
		/// <returns>Numero aleatorio (int)</returns>
		int generateRange(int a, int b);
		#pragma endregion

		#pragma region Estructuras de FORGE aleatorias
		/// <summary>
		/// Genera un Vector3 aleatorio con valores normalizados
		/// </summary>
		/// <returns>Vector3 normalizado</returns>
		Vector3 getRandomVector();
		/// <summary>
		///  Genera un Quaternion aleatorio con valores normalizados
		/// </summary>
		/// <returns>Quaternion</returns>
		Quaternion getRandomQuaternion();
		#pragma endregion
	};
}
#endif