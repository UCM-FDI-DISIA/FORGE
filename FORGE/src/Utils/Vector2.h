#pragma once
#ifndef VECTOR2_H_
#define VECTOR2_H_

namespace forge {
	class Vector2 {
	private:
		// Primera coordenada
		float x;
		// Segunda coordenada
		float y;
	public:
		/// <summary>
		/// Constructora por defecto de la clase Vector2D
		/// </summary>	
		Vector2();
		/// <summary>
		/// Constructora a partir de parametros
		/// </summary>	
		Vector2(float _x, float _y);
		/// <summary>
		/// Constructora a partir de otro vector
		/// </summary>	
		Vector2(const Vector2& v);
		/// <summary>
		/// Destructora por defecto de la clase Vector2D
		/// </summary>
		~Vector2();

		/// <summary>
		/// Suma dos vectores
		/// </summary>	
		Vector2 operator+(const Vector2& v) const;
		/// <summary>
		/// Resta dos vectores
		/// </summary>	
		Vector2 operator-(const Vector2& v) const;
		/// <summary>
		/// Multiplica un vector por un escalar
		/// </summary>	
		Vector2 operator*(float e) const;
		/// <summary>
		/// Divide un vector por un escalar
		/// </summary>
		Vector2 operator/(float e) const;
		/// <summary>
		/// Producto escalar
		/// </summary>
		float operator*(const Vector2& v) const;
		/// <summary>
		/// Igualdad de dos vectores
		/// </summary>
		bool operator==(const Vector2& v) const;
		/// <summary>
		/// Desigualdad de dos vectores
		/// </summary>
		bool operator!=(const Vector2& v) const;

		/// <summary>
		/// Calcula el modulo de un vector
		/// </summary>
		float magnitude() const;
		/// <summary>
		/// Normaliza un vector
		/// </summary>
		Vector2 normalize() const;

		/// <summary>
		/// Devuelve el valor de la coordenada X
		/// </summary>	
		float getX() const;
		/// <summary>
		/// Devuelve el valor de la coordenada y
		/// </summary>	
		float getY() const;

		/// <summary>
		/// Setea el valor de la coordenada X
		/// </summary>	
		void setX(float _x);
		/// <summary>
		/// Setea el valor de la coordenada y
		/// </summary>	
		void setY(float _y);
		/// <summary>
		/// Setea un vector a través de otro vector
		/// </summary>	
		void set(const Vector2& v);
		/// <summary>
		/// Setea un vector a través de floats
		/// </summary>	
		void set(float _x, float _y);

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

