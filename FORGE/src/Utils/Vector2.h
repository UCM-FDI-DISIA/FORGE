#pragma once
#ifndef VECTOR2_H_
#define VECTOR2_H_

#include "ForgeExport.h"

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
		FORGE_API Vector2();
		/// <summary>
		/// Constructora a partir de parametros
		/// </summary>
		/// <param name="_x">Componente en X</param>
		/// <param name="_y">Componente en Y</param>
		FORGE_API Vector2(float _x, float _y);
		/// <summary>
		/// Constructora a partir de otro vector
		/// </summary>
		/// <param name="v">Vector a copiar</param>
		FORGE_API Vector2(const Vector2& v);
		/// <summary>
		/// Constructor de vector uniforme: Vector2(v,v)
		/// </summary>
		/// <param name="e">Componente X e Y</param>
		FORGE_API Vector2(float e);
		/// <summary>
		/// Destructora por defecto de la clase Vector2D
		/// </summary>
		FORGE_API ~Vector2();
		#pragma endregion

		#pragma region Operadores
		/// <summary>
		/// Suma dos vectores
		/// </summary>
		/// <param name="v">Vector a sumar</param>
		/// <returns>El vector resultante</returns>
		FORGE_API Vector2 operator+(const Vector2& v) const;
		/// <summary>
		/// Resta dos vectores
		/// </summary>
		/// <param name="v">Vector a restar</param>
		/// <returns>El vector resultante</returns>
		FORGE_API Vector2 operator-(const Vector2& v) const;
		/// <summary>
		/// Multiplica un vector por un escalar
		/// </summary>
		/// <param name="e">Escalar por el que multiplicar</param>
		/// <returns>El vector resultante</returns>
		FORGE_API Vector2 operator*(float e) const;
		/// <summary>
		/// Divide un vector por un escalar
		/// </summary>
		/// <param name="e">Escalar por el que dividir</param>
		/// <returns>El vector resultante</returns>
		FORGE_API Vector2 operator/(float e) const;
		/// <summary>
		/// Divide un vector entre las componentes de otro
		/// </summary>
		/// <param name="v">vector por el que dividir</param>
		/// <returns>El vector resultante</returns>
		FORGE_API Vector2 operator/(Vector2 const& v) const;
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
		FORGE_API Vector2 operator*(const Vector2& v) const;
		/// <summary>
		/// Igualdad de dos vectores
		/// </summary>
		/// <param name="v">Vector a comparar</param>
		/// <returns>Resultado de la comprobacion</returns>
		FORGE_API bool operator==(const Vector2& v) const;
		/// <summary>
		/// Desigualdad de dos vectores
		/// </summary>
		/// <param name="v">Vector a comparar</param>
		/// <returns>Resultado de la comprobacion</returns>
		FORGE_API bool operator!=(const Vector2& v) const;
		/// <summary>
		/// Suma de dos vectores
		/// </summary>
		/// <param name="v">Vector a sumar</param>
		/// <returns>El vector actualizado</returns>
		FORGE_API Vector2 operator+=(const Vector2& v);
		/// <summary>
		/// Multiplicacion de dos vectores
		/// </summary>
		/// <param name="v">Vector por el que multiplicar</param>
		/// <returns>El vector actualizado</returns>
		FORGE_API Vector2 operator*=(const Vector2& v);
		/// <summary>
		/// Multiplicacion de un vector por un float
		/// </summary>
		/// <param name="e">Escalar por el que multiplicar</param>
		/// <returns>El vector actualizado</returns>
		FORGE_API Vector2 operator*=(float e);
		#pragma endregion

		/// <summary>
		/// Calcula el modulo de un vector
		/// </summary>
		/// <returns>El modulo</returns>
		FORGE_API float magnitude() const;
		/// <summary>
		/// Normaliza un vector
		/// </summary>
		/// <returns>Vector normalizado</returns>
		FORGE_API Vector2 normalize() const;

		#pragma region Getters
		/// <summary>
		/// Devuelve el valor de la coordenada X
		/// </summary>	
		/// <returns>La coordenada X</returns> 
		FORGE_API float getX() const;
		/// <summary>
		/// Devuelve el valor de la coordenada y
		/// </summary>	
		/// <returns>La coordenada Y</returns> 
		FORGE_API float getY() const;
		#pragma endregion

		#pragma region Setters
		/// <summary>
		/// Setea el valor de la coordenada X
		/// </summary>
		/// <param name="_x">Nuevo valor de X</param>
		FORGE_API void setX(float _x);
		/// <summary>
		/// Setea el valor de la coordenada y
		/// </summary>
		/// <param name="_y">Nuevo valor de Y</param>
		FORGE_API void setY(float _y);
		/// <summary>
		/// Setea un vector a traves de otro vector
		/// </summary>
		/// <param name="v">Vector a asignar</param>
		FORGE_API void set(const Vector2& v);
		/// <summary>
		/// Setea un vector a traves de floats
		/// </summary>
		/// <param name="_x">Nuevo valor de X</param>
		/// <param name="_y">Nuevo valor de Y</param>
		FORGE_API void set(float _x, float _y);
		#pragma endregion

		#pragma region Constantes
		FORGE_API_VAR static const Vector2 ZERO;
		FORGE_API_VAR static const Vector2 RIGHT;
		FORGE_API_VAR static const Vector2 LEFT;
		FORGE_API_VAR static const Vector2 UP;
		FORGE_API_VAR static const Vector2 DOWN;
		FORGE_API_VAR static const Vector2 UNIT;
		#pragma endregion
	};
}
#endif