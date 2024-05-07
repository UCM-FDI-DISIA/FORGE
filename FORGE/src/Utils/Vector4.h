#pragma once
#ifndef VECTOR4_H_
#define VECTOR4_H_

namespace forge {
	class Vector4 {
	private:
		// Primera coordenada
		float x;
		// Segunda coordenada
		float y;
		// Tercera coordenada
		float z;
		// Cuarta coordenada
		float w;
	public:
		#pragma region Constructoras
		/// <summary>
		/// Constructora por defecto de la clase Vector4
		/// </summary>	
		Vector4();
		/// <summary>
		/// Constructora a partir de parametros
		/// </summary>
		/// <param name="_x">Componente en X</param>
		/// <param name="_y">Componente en Y</param>
		/// <param name="_z">Componente en Z</param>
		/// <param name="_w">Componente en W</param>
		Vector4(float _x, float _y, float _z, float _w);
		/// <summary>
		/// Constructora a partir de un solo parametro (vector uniforme)
		/// </summary>
		/// <param name="e">Componente en X, Y, Z y W</param>
		Vector4(float e);
		/// <summary>
		/// Constructora a partir de otro vector
		/// </summary>
		/// <param name="v">Vector a copiar</param>
		Vector4(const Vector4& v);		
		/// <summary>
		/// Destructora por defecto de la clase Vector4
		/// </summary>
		~Vector4();
		#pragma endregion

		#pragma region Getters
		/// <summary>
		/// Acceso a la componente en X del vector
		/// </summary>
		/// <returns>Devuelve la componente en X</returns>
		float getX() const;

		/// <summary>
		/// Acceso a la componente en Y del vector
		/// </summary>
		/// <returns>Devuelve la componente en Y</returns>
		float getY() const;

		/// <summary>
		/// Acceso a la componente en Z del vector
		/// </summary>
		/// <returns>Devuelve la componente en Z</returns>
		float getZ() const;

		/// <summary>
		/// Acceso a la componente en W del vector
		/// </summary>
		/// <returns>Devuelve la componente en W</returns>
		float getW() const;
		#pragma endregion

		#pragma region Setters
		/// <summary>
		/// Setea el valor de la coordenada X
		/// </summary>
		/// <param name="_x">Nuevo valor de X</param>
		void setX(float _x);
		/// <summary>
		/// Setea el valor de la coordenada Y
		/// </summary>
		/// <param name="_y">Nuevo valor de Y</param>
		void setY(float _y);
		/// <summary>
		/// Setea el valor de la coordenada Z
		/// </summary>
		/// <param name="_z">Nuevo valor de Z</param>
		void setZ(float _z);
		/// <summary>
		/// Setea el valor de la coordenada W
		/// </summary>
		/// <param name="_w">Nuevo valor de W</param>
		void setW(float _w);
		/// <summary>
		/// Setea un vector a traves de otro vector
		/// </summary>
		/// <param name="v">Vector a asignar</param>
		void set(const Vector4& v);
		/// <summary>
		/// Setea un vector a traves de floats
		/// </summary>
		/// <param name="_x">Nuevo valor de X</param>
		/// <param name="_y">Nuevo valor de Y</param>
		/// <param name="_z">Nuevo valor de Z</param>
		/// <param name="_w">Nuevo valor de W</param>
		void set(float _x, float _y, float _z, float _w);
		#pragma endregion

		#pragma region Operadores
		/// <summary>
		/// Suma los vectores
		/// </summary>
		/// <param name="w">Vector sumando</param>
		/// <returns>El vector suma resultante</returns>
		Vector4 operator+(const Vector4& w) const;
		#pragma endregion
	};
}
#endif


