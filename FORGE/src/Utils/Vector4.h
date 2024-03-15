#pragma once
#ifndef VECTOR4_H_
#define VECTOR4_H_
#include "imgui.h"
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
		Vector4(float _x, float _y, float _z, float _w);
		/// <summary>
		/// Constructora a partir de otro vector
		/// </summary>	
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
		void setX(float x_);
		/// <summary>
		/// Setea el valor de la coordenada Y
		/// </summary>	
		void setY(float y_);
		/// <summary>
		/// Setea el valor de la coordenada Z
		/// </summary>	
		void setZ(float z_);
		/// <summary>
		/// Setea el valor de la coordenada W
		/// </summary>	
		void setW(float w_);
		/// <summary>
		/// Setea un vector a través de otro vector
		/// </summary>	
		void set(const Vector4& v);
		/// <summary>
		/// Setea un vector a través de floats
		/// </summary>	
		void set(float _x, float _y, float _z, float _w);
		#pragma endregion

		#pragma region Conversiones
		/// <summary>
		/// Sobrecarga del operador de conversión a ImVec4
		/// </summary>	
		operator ImVec4() const;
		#pragma endregion
	};
}
#endif


