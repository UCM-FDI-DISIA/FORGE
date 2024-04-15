#pragma once
#include "Vector3.h"
#include "ForgeExport.h"

namespace Ogre {
	class Quaternion;
}

class btQuaternion;
namespace forge {
	/// TO DO: Adaptar para que los set y get de los parametros los pueda tratar el usuario como par rotacion. Habrá que guardar el angulo o el seno.
	class Quaternion {
	private:
		float x;
		float y;
		float z;
		float w;

	public:
		#pragma region Constructores
		/// <summary>
		/// Constructor predeterminado: Quaternion(0,0,0,0)
		/// </summary>
		FORGE_API Quaternion();

		/// <summary>
		/// Constructor completo
		/// </summary>
		/// <param name="_x">Valor en la componente X</param>
		/// <param name="_y">Valor en la componente Y</param>
		/// <param name="_z">Valor en la componente Z</param>
		/// <param name="_angle">Valor del angulo del par rotacion</param>
		FORGE_API Quaternion(float _x, float _y, float _z, float _angle);

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
		void normalize();

		#pragma region Setters
		/// <summary>
		/// Asigna un nuevo valor a la componente en X del par-rotacion
		/// </summary>
		/// <param name="newX">Nuevo valor en X</param>
		FORGE_API void setX(float newX);

		/// <summary>
		/// Asigna un nuevo valor a la componente en Y del par-rotacion
		/// </summary>
		/// <param name="newY">Nuevo valor en Y</param>
		FORGE_API void setY(float newY);

		/// <summary>
		/// Asigna un nuevo valor a la componente en Z del par-rotacion
		/// </summary>
		/// <param name="newZ">Nuevo valor en Z</param>
		FORGE_API void setZ(float newZ);

		/// <summary>
		/// Asigna un nuevo angulo
		/// </summary>
		/// <param name="newAngle">Nuevo valor del angulo del par rotacion</param>
		FORGE_API void setAngle(float newAngle);

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
		FORGE_API float getX() const;

		/// <summary>
		/// Acceso a la componente en Y del par-rotacion que representa el cuaternion
		/// </summary>
		/// <returns>Devuelve la orientacion en Y</returns>
		FORGE_API float getY() const;

		/// <summary>
		/// Acceso a la componente en Z del par-rotacion que representa el cuaternion
		/// </summary>
		/// <returns>Devuelve la orientacion en Z</returns>
		FORGE_API float getZ() const;

		/// <summary>
		/// Acceso al angulo del cuaternion
		/// </summary>
		/// <returns>Devuelve el angulo entre 0 y 2PI</returns>
		FORGE_API float getAngle() const;
		#pragma endregion

		#pragma region Conversiones
		/// <summary>
		/// Conversion implicita de forge::Quaternion a Ogre::Quaternion
		/// </summary>
		operator Ogre::Quaternion() const;

		/// <summary>
		/// Constructor por copia de Ogre::Quaternion
		/// </summary>
		/// <param name="q">Cuaternion de Ogre a copiar</param>
		Quaternion(const Ogre::Quaternion& q);

		/// <summary>
		/// Constructor por copia de referencia a R value de btQuaternion
		/// </summary>
		/// <param name="q">Cuaternion de Bullet a copiar</param>
		Quaternion(Ogre::Quaternion&& q) noexcept;

		/// <summary>
		/// Asigna la informacion de Q a este cuaternion
		/// </summary>
		/// <param name="q">Cuaternion de Bullet a copiar</param>
		/// <returns>Cuaternion actualizado</returns>
		Quaternion& operator=(const Ogre::Quaternion& q);

		/// <summary>
		/// Conversion implicita de forge::Quaternion a btQuaternion
		/// </summary>
		operator btQuaternion() const;

		/// <summary>
		/// Constructor por copia de Ogre::Quaternion
		/// </summary>
		/// <param name="q">Cuaternion de Bullet a copiar</param>
		Quaternion(const btQuaternion& q);

		/// <summary>
		/// Constructor por copia de referencia a R value de Ogre::Quaternion
		/// </summary>
		/// <param name="q">Cuaternion de Bullet a copiar</param>
		Quaternion(btQuaternion&& q) noexcept;

		/// <summary>
		/// Asigna la informacion de Q a este cuaternion
		/// </summary>
		/// <param name="q">Cuaternion de Bullet a copiar</param>
		/// <returns>Cuaternion actualizado</returns>
		Quaternion& operator=(const btQuaternion& q);
		#pragma endregion

		static const FORGE_API_VAR Quaternion IDENTITY;
	};
}