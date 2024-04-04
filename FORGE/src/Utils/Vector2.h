#pragma once

#ifndef VECTOR2_H_
#define VECTOR2_H_

#include "imgui.h"

namespace forge {
	class Vector2 {
	private:
		// Primera coordenada
		float x;
		// Segunda coordenada
		float y;
	public:
		#pragma region Constructoras
		/// <summary>
		/// Constructora por defecto de la clase Vector2D
		/// </summary>	
		Vector2();
		/// <summary>
		/// Constructora a partir de parametros
		/// </summary>
		/// <param name="_x">Componente en X</param>
		/// <param name="_x">Componente en Y</param>
		Vector2(float _x, float _y);
		/// <summary>
		/// Constructora a partir de otro vector
		/// </summary>
		/// <param name="v">Vector a copiar</param>
		Vector2(const Vector2& v);
		/// <summary>
		/// Constructor de vector uniforme: Vector2(v,v)
		/// </summary>
		/// <param name="e">Componente X e Y</param>
		Vector2(float e);
		/// <summary>
		/// Destructora por defecto de la clase Vector2D
		/// </summary>
		~Vector2();
		#pragma endregion

		#pragma region Operadores
		/// <summary>
		/// Suma dos vectores
		/// </summary>
		/// <param name="v">Vector a sumar</param>
		/// <returns>El vector resultante</returns>
		Vector2 operator+(const Vector2& v) const;
		/// <summary>
		/// Resta dos vectores
		/// </summary>
		/// <param name="v">Vector a restar</param>
		/// <returns>El vector resultante</returns>
		Vector2 operator-(const Vector2& v) const;
		/// <summary>
		/// Multiplica un vector por un escalar
		/// </summary>
		/// <param name="e">Escalar por el que multiplicar</param>
		/// <returns>El vector resultante</returns>
		Vector2 operator*(float e) const;
		/// <summary>
		/// Divide un vector por un escalar
		/// </summary>
		/// <param name="e">Escalar por el que dividir</param>
		/// <returns>El vector resultante</returns>
		Vector2 operator/(float e) const;
		/// <summary>
		/// Producto escalar
		/// </summary>
		/// <param name="v">Vector por el que multiplicar</param>
		/// <returns>El escalar resultante</returns>
		//float operator*(const Vector2& v) const;
		/// <summary>
		/// Producto por componentes (Hadamard)
		/// </summary>
		/// <param name="v">Vector por el que multiplicar</param>
		/// <returns>El escalar resultante</returns>
		Vector2 operator*(const Vector2& v) const;
		/// <summary>
		/// Igualdad de dos vectores
		/// </summary>
		/// <param name="v">Vector a comparar</param>
		/// <returns>Resultado de la comprobacion</returns>
		bool operator==(const Vector2& v) const;
		/// <summary>
		/// Desigualdad de dos vectores
		/// </summary>
		/// <param name="v">Vector a comparar</param>
		/// <returns>Resultado de la comprobacion</returns>
		bool operator!=(const Vector2& v) const;
		/// <summary>
		/// Suma de dos vectores
		/// </summary>
		/// <param name="v">Vector a sumar</param>
		/// <returns>El vector actualizado</returns>
		Vector2 operator+=(const Vector2& v);
		/// <summary>
		/// Multiplicacion de dos vectores
		/// </summary>
		/// <param name="v">Vector por el que multiplicar</param>
		/// <returns>El vector actualizado</returns>
		Vector2 operator*=(const Vector2& v);
		/// <summary>
		/// Multiplicacion de un vector por un float
		/// </summary>
		/// <param name="e">Escalar por el que multiplicar</param>
		/// <returns>El vector actualizado</returns>
		Vector2 operator*=(float e);
		#pragma endregion

		/// <summary>
		/// Calcula el modulo de un vector
		/// </summary>
		/// <returns>El modulo</returns>
		float magnitude() const;
		/// <summary>
		/// Normaliza un vector
		/// </summary>
		/// <returns>Vector normalizado</returns>
		Vector2 normalize() const;

		#pragma region Getters
		/// <summary>
		/// Devuelve el valor de la coordenada X
		/// </summary>	
		/// <returns>La coordenada X</returns> 
		float getX() const;
		/// <summary>
		/// Devuelve el valor de la coordenada y
		/// </summary>	
		/// <returns>La coordenada Y</returns> 
		float getY() const;
		#pragma endregion

		#pragma region Setters
		/// <summary>
		/// Setea el valor de la coordenada X
		/// </summary>
		/// <param name="_x">Nuevo valor de X</param>
		void setX(float _x);
		/// <summary>
		/// Setea el valor de la coordenada y
		/// </summary>
		/// <param name="_y">Nuevo valor de Y</param>
		void setY(float _y);
		/// <summary>
		/// Setea un vector a través de otro vector
		/// </summary>
		/// <param name="v">Vector a asignar</param>
		void set(const Vector2& v);
		/// <summary>
		/// Setea un vector a través de floats
		/// </summary>
		/// <param name="_x">Nuevo valor de X</param>
		/// <param name="_y">Nuevo valor de Y</param>
		void set(float _x, float _y);
		#pragma endregion

		#pragma region Conversiones
		/// <summary>
		/// Sobrecarga del operador de conversión a ImVec2
		/// </summary>
		/// <returns>ImVec2 convertido</returns>
		operator ImVec2() const;
		#pragma endregion

		#pragma region Constantes
		static const Vector2 ZERO;
		static const Vector2 RIGHT;
		static const Vector2 LEFT;
		static const Vector2 UP;
		static const Vector2 DOWN;
		static const Vector2 UNIT;
		#pragma endregion
	};
}
#endif