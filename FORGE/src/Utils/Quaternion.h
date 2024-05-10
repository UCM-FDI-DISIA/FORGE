#pragma once
#include "Vector3.h"
#include "ForgeExport.h"

namespace forge {
	class Quaternion {
	private:
		float x;
		float y;
		float z;
		float w;

		/// <summary>
		/// Se asegura de que el si el Quaternion es invalido lo asigna al identidad
		/// </summary>
		void validate();

	public:
		#pragma region Constructores
		/// <summary>
		/// Constructor predeterminado: Quaternion(0,0,0,1)
		/// </summary>
		FORGE_API Quaternion();

		/// <summary>
		/// Constructor completo a partir de valores de Quaternion
		/// </summary>
		/// <param name="_x">Valor en la componente X</param>
		/// <param name="_y">Valor en la componente Y</param>
		/// <param name="_z">Valor en la componente Z</param>
		/// <param name="_w">Valor en la componente W</param>
		FORGE_API Quaternion(float _x, float _y, float _z, float _w);

		/// <summary>
		/// Constructor a partir de un par rotacion
		/// </summary>
		/// <param name="vec">Direccion a la que miraria la rotacion del objeto</param>
		/// <param name="angle">Rotacion alrededor del vector introducido</param>
		/// <returns></returns>
		FORGE_API Quaternion(Vector3 const& vec, float angle);
		/// <summary>
		/// Constructor por copia
		/// </summary>
		/// <param name="q">Cuaternion a copiar</param>
		FORGE_API Quaternion(const Quaternion& q);

		/// <summary>
		/// Constructor por copia (referencia)
		/// </summary>
		/// <param name="q">Cuaternion a copiar</param>
		FORGE_API Quaternion(Quaternion&& q) noexcept;

		/// <summary>
		/// Constructor por copia (puntero)
		/// </summary>
		/// <param name="q">Cuaternion a copiar</param>
		FORGE_API Quaternion(const Quaternion* q);

		/// <summary>
		/// Contructor a partir de un vector (Euleriano)
		/// </summary>
		/// <param name="e">Vector euleriano a comvertir en cuaternion</param>
		FORGE_API Quaternion(const Vector3& e);

		FORGE_API ~Quaternion();
		#pragma endregion

		#pragma region Operadores
		/// <summary>
		/// Asigna la informacion de Q a este cuaternion
		/// </summary>
		/// <param name="q">Cuaternion a copiar</param>
		/// <returns>Cuaternion actualizado</returns>
		FORGE_API Quaternion& operator=(const Quaternion& q);
		
		/// <summary>
		/// Asigna la informacion del vector E (Euleriano) a este cuaternion
		/// </summary>
		/// <param name="e">Euleriano a convertir</param>
		/// <returns>Cuaternion actualizado</returns>
		FORGE_API Quaternion& operator=(const Vector3& e);

		/// <summary>
		/// Calcula el producto escalar de los quaterniones
		/// </summary>
		/// <param name="q">El otro cuaternion</param>
		/// <returns>Producto escalar de ambos</returns>
		FORGE_API float dot(const Quaternion& q) const;
		
		/// <summary>
		/// Multiplicacion polinomial de cuaterniones
		/// </summary>
		/// <param name="q">El otro cuaternion</param>
		/// <returns>El resultado de la multiplicacion polinomial</returns>
		FORGE_API Quaternion operator*(const Quaternion& q) const;
		
		/// <summary>
		/// Calcula la multiplicacion polinomial de cuaterniones y asigna su resultado a este cuaternion
		/// </summary>
		/// <param name="q">El otro cuaternion</param>
		/// <returns>El cuaternion actualizado</returns>
		FORGE_API Quaternion operator*=(const Quaternion& q);
		
		/// <summary>
		/// Rotacion de un vector aplicando este cuaternion
		/// </summary>
		/// <param name="v">El vector a rotar</param>
		/// <returns>El vector V rotado</returns>
		FORGE_API Vector3 operator*(const Vector3& v) const;

		/// <summary>
		/// Compara dos cuaterniones. Seran iguales si su producto escalar es igual a 1
		/// </summary>
		/// <param name="q">El otro cuaternion</param>
		/// <returns>Si son iguales</returns>
		FORGE_API bool operator==(const Quaternion& q) const;
		
		/// <summary>
		/// Compara dos cuaterniones. Seran distintos si su producto escalar es menor a 1
		/// </summary>
		/// <param name="q">El otro cuaternion</param>
		/// <returns>Si son distintos</returns>
		FORGE_API bool operator!=(const Quaternion& q) const;
		#pragma endregion

		/// <summary>
		/// Calcula un vector Euleriano a partir del cuaternion
		/// </summary>
		/// <returns>El vector Euleriano constante</returns>
		FORGE_API Vector3 toEuler() const;

		/// <summary>
		/// Normaliza el vector del quaternion
		/// </summary>
		FORGE_API void normalize();

		/// <summary>
		/// Devuelve el Quaternion inverso
		/// </summary>
		/// <returns>El Quaternion inverso</returns>
		FORGE_API Quaternion inversed() const;

		#pragma region Setters
		/// <summary>
		/// Asigna un nuevo valor a la componente en X del par-rotacion
		/// </summary>
		/// <param name="newX">Nuevo valor en X</param>
		FORGE_API void setRotPairX(float newX);

		/// <summary>
		/// Asigna un nuevo valor a la componente en Y del par-rotacion
		/// </summary>
		/// <param name="newY">Nuevo valor en Y</param>
		FORGE_API void setRotPairY(float newY);

		/// <summary>
		/// Asigna un nuevo valor a la componente en Z del par-rotacion
		/// </summary>
		/// <param name="newZ">Nuevo valor en Z</param>
		FORGE_API void setRotPairZ(float newZ);

		/// <summary>
		/// Asigna un nuevo valor a la componente en X directamente
		/// </summary>
		/// <param name="newX">Nuevo valor en X</param>
		FORGE_API void setX(float newX);

		/// <summary>
		/// Asigna un nuevo valor a la componente en Y directamente
		/// </summary>
		/// <param name="newY">Nuevo valor en Y</param>
		FORGE_API void setY(float newY);

		/// <summary>
		/// Asigna un nuevo valor a la componente en Z directamente
		/// </summary>
		/// <param name="newZ">Nuevo valor en Z</param>
		FORGE_API void setZ(float newZ);

		/// <summary>
		/// Asigna un nuevo valor a la componente en W del par-rotacion
		/// </summary>
		/// <param name="newW">Nuevo valor en W</param>
		FORGE_API void setW(float newW);

		/// <summary>
		/// Asigna un nuevo angulo
		/// </summary>
		/// <param name="newAngle">Nuevo valor del angulo del par rotacion</param>
		FORGE_API void setAngle(float newAngle);

		/// <summary>
		/// Consigue un cuaternion para mirar de una posición a otro punto
		/// </summary>
		/// <param name="lookTo">Punto a mirar</param>
		/// <param name="pos">Posición actual</param> 
		FORGE_API void lookTo(forge::Vector3 const& lookTo, forge::Vector3 const& pos);

		/// <summary>
		/// Asigna nuevos valores al cuaternion
		/// </summary>
		/// <param name="newX">Valor del par-rotacion en el eje X</param>
		/// <param name="newY">Valor del par-rotacion en el eje Y</param>
		/// <param name="newZ">Valor del par-rotacion en el eje Z</param>
		/// <param name="newAngle">Valor del angulo del par rotacion</param>
		FORGE_API void set(float newX, float newY, float newZ, float newAngle);

		/// <summary>
		/// Asigna nuevos valores al cuaternion copiando los de Q
		/// </summary>
		/// <param name="q">Cuaternion a copiar</param>
		FORGE_API void set(const Quaternion& q);

		/// <summary>
		/// Asigna nuevos valores al cuaternion copiando los de Q
		/// </summary>
		/// <param name="q">Cuaternion a copiar (referencia)</param>
		FORGE_API void set(const Quaternion&& q);

		/// <summary>
		/// Asigna nuevos valores al cuaternion copiando los del cuaternion al que apunta Q
		/// </summary>
		/// <param name="q">Cuaternion a copiar (puntero)</param>
		FORGE_API void set(const Quaternion* q);
		#pragma endregion

		#pragma region Getters
		/// <summary>
		/// Acceso a la componente en X del par-rotacion que representa el cuaternion
		/// </summary>
		/// <returns>Devuelve la orientacion en X</returns>
		FORGE_API float getRotPairX() const;

		/// <summary>
		/// Acceso a la componente en Y del par-rotacion que representa el cuaternion
		/// </summary>
		/// <returns>Devuelve la orientacion en Y</returns>
		FORGE_API float getRotPairY() const;

		/// <summary>
		/// Acceso a la componente en Z del par-rotacion que representa el cuaternion
		/// </summary>
		/// <returns>Devuelve la orientacion en Z</returns>
		FORGE_API float getRotPairZ() const;

		/// <summary>
		/// Devuelve el valor a la componente en X directamente
		/// </summary>
		FORGE_API float getX() const;

		/// <summary>
		/// Devuelve el valor a la componente en Y directamente
		/// </summary>
		FORGE_API float getY() const;

		/// <summary>
		/// Devuelve el valor a la componente en Z directamente
		/// </summary>
		FORGE_API float getZ() const;

		/// <summary>
		/// Acceso a la componente en W del par-rotacion que representa el cuaternion
		/// </summary>
		/// <returns>Devuelve la orientacion en W</returns>
		FORGE_API float getW() const;

		/// <summary>
		/// Acceso al angulo del cuaternion
		/// </summary>
		/// <returns>Devuelve el angulo entre 0 y 2PI</returns>
		FORGE_API float getAngle() const;
		#pragma endregion

		static const FORGE_API_VAR Quaternion IDENTITY;
	};
}