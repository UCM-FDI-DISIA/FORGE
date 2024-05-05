#pragma once
#ifndef VECTOR3_H_
#define VECTOR3_H_
#include "ForgeExport.h"
namespace Ogre {
	template <int dims, typename T> class Vector;
	typedef Vector<3, float> Vector3f;
}
namespace irrklang{
	template <class T> class vec3d;
	typedef vec3d<float> vec3df;
}
namespace forge {
	class Vector3 {
	private:
		float x;
		float y;
		float z;
	protected:

	public:
		#pragma region Constructores
		/// <summary>
		/// Constructor predeterminado: Vector(0,0,0)
		/// </summary>
		FORGE_API Vector3();

		/// <summary>
		/// Constructor completo: Vector3(_x, _y, _z)
		/// </summary>
		/// <param name="_x">Componente en X</param>
		/// <param name="_y">Componente en Y</param>
		/// <param name="_z">Componente en Z</param>
		FORGE_API Vector3(float _x, float _y, float _z);

		/// <summary>
		/// Constructor de vector uniforme: Vector3(v,v,v)
		/// </summary>
		/// <param name="v"></param>
		FORGE_API Vector3(float v);

		/// <summary>
		/// Constructor por copia
		/// </summary>
		/// <param name="w">Vector a copiar</param>
		FORGE_API Vector3(const Vector3& w);

		/// <summary>
		/// Constructor por copia de referencia
		/// </summary>
		/// <param name="w">Vector a copiar</param>
		FORGE_API Vector3(Vector3&& w) noexcept;

		/// <summary>
		/// Constructor por copia de puntero
		/// </summary>
		/// <param name="w">Vector a copiar</param>
		FORGE_API Vector3(const Vector3* w);

		FORGE_API ~Vector3();
		#pragma endregion

		/// <summary>
		/// Calcula la longitud del vector
		/// </summary>
		/// <returns>La longitud de V</returns>
		FORGE_API float magnitude() const;

		/// <summary>
		/// Calcula la longitud del vector al cuadrado
		/// </summary>
		/// <returns>La longitud de V al cuadrado</returns>
		FORGE_API float sqrMagnitude() const;

		/// <summary>
		/// Calcula el vector normalizado sin modificar el actual
		/// </summary>
		/// <returns>El vector normalizado</returns>
		FORGE_API Vector3 normalized() const;

		/// <summary>
		/// Normaliza el vector
		/// </summary>
		/// <returns>Una referencia al vector normalizado</returns>
		FORGE_API Vector3* normalize();

		/// <summary>
		/// Calcula la longitud entre 2 puntos
		/// </summary>
		/// <param name="w">El punto destino</param>
		/// <returns>La longitud de V a W</returns>
		FORGE_API float distance(const Vector3& w) const;

		/// <summary>
		/// Devuelve un vector formado por el maximo valor de cada componente
		/// </summary>
		/// <param name="w">El otro vector</param>
		/// <returns>El vector maximizado con respecto a V y W</returns>
		FORGE_API Vector3 maxV(const Vector3& w) const;

		/// <summary>
		/// Devuelve un vector formado por el minimo valor de cada componente
		/// </summary>
		/// <param name="w">El otro vector</param>
		/// <returns>El vector minimizado con respecto a V y W</returns>
		FORGE_API Vector3 minV(const Vector3& w) const;

		/// <summary>
		/// Entendiendo V como vector inicial y W como vector destino, 
		/// calcula un vector situado entre V y W con un valor de proporcion t
		/// </summary>
		/// <param name="w">El vector destino</param>
		/// <param name="t">La proprcion entre V y W</param>
		/// <returns></returns>
		FORGE_API Vector3 lerp(const Vector3& w, float t) const;

		#pragma region Operadores
		/// <summary>
		/// Asigna la informacion de W a este vector
		/// </summary>
		/// <param name="w">Vector a asignar</param>
		/// <returns>El vector actualizado</returns>
		FORGE_API Vector3& operator=(const Vector3& w);

		/// <summary>
		/// Suma los vectores
		/// </summary>
		/// <param name="w">Vector sumando</param>
		/// <returns>El vector suma resultante</returns>
		FORGE_API Vector3 operator+(const Vector3& w) const;

		/// <summary>
		/// Suma los vectores y asigna el vector resultante a este
		/// </summary>
		/// <param name="w">Vector sumando</param>
		/// <returns>El vector actualizado (con el valor de la suma de V y W)</returns>
		FORGE_API Vector3 operator+=(const Vector3& w);

		/// <summary>
		/// Resta los vectores
		/// </summary>
		/// <param name="w">Vector sustraendo</param>
		/// <returns>El vector resta resultante</returns>
		FORGE_API Vector3 operator-(const Vector3& w) const;

		/// <summary>
		/// Multiplicacion por constante (escalado)
		/// </summary>
		/// <param name="d">Valor de escalado</param>
		/// <returns>El vector escalado</returns>
		FORGE_API Vector3 operator*(float d) const;

		/// <summary>
		/// Division por constante (escalado)
		/// </summary>
		/// <param name="d">Valor de escalado</param>
		/// <returns>El vector escalado</returns>
		FORGE_API Vector3 operator/(float d) const;

		/// <summary>
		/// Multiplicacion por componentes (Hadamard)
		/// </summary>
		/// <param name="w">Vector producto</param>
		/// <returns>El vector resultante</returns>
		FORGE_API Vector3 operator*(const Vector3& w) const;

		/// <summary>
		/// Devision por componentes
		/// </summary>
		/// <param name="w">Vector divisor</param>
		/// <returns>El vector resultante</returns>
		FORGE_API Vector3 operator/(const Vector3& w) const;

		/// <summary>
		/// Multiplicacion por componentes (Hadamard) y asignacion
		/// </summary>
		/// <param name="w">Vector producto</param>
		/// <returns>El vector actualizado (resultante de la operacion de V y W)</returns>
		FORGE_API Vector3 operator*=(const Vector3& w);

		/// <summary>
		/// Compara dos vectores. Seran iguales si la diferencia entre componentes es muy proxima o igual a 0
		/// </summary>
		/// <param name="w">Vector con el que se compara</param>
		/// <returns>Si son iguales</returns>
		FORGE_API bool operator==(const Vector3& w) const;

		/// <summary>
		/// Compara dos vectores. Seran dsitintos si la diferencia entre componentes es mayor que 0 (con cierto margen de error)
		/// </summary>
		/// <param name="w">Vector con el que se compara</param>
		/// <returns>Si son distintos</returns>
		FORGE_API bool operator!=(const Vector3& w) const;
		#pragma endregion

		#pragma region Angulos
		/// <summary>
		/// Calcula el angulo formado por dos vectores en 3 dimensiones
		/// </summary>
		/// <param name="w">El otro Vector3 que conforma el angulo</param>
		/// <returns>El angulo que forman ambos vectores</returns>
		FORGE_API double angle(const Vector3& w) const;

		/// <summary>
		/// Dado un vector normal de un plano, devuelve el vector resultante de 
		/// la reflexion del vector en dicho plano
		/// </summary>
		/// <param name="normal">Vector normal del plano</param>
		/// <returns>El vector resultante de reflexion</returns>
		FORGE_API Vector3 reflect(const Vector3& normal) const;

		/// <summary>
		/// Siendo V este vector, calcula la proyeccion de V sobre W
		/// </summary>
		/// <param name="w">Vector sobre el que se proyecta v</param>
		/// <returns>La proyeccion de v sobre w</returns>
		FORGE_API Vector3 project(const Vector3& w) const;

		/// <summary>
		/// Calcula el producto vectorial de V y W: v x w
		/// </summary>
		/// <param name="w">Segundo vector</param>
		/// <returns>Producto vectorial de ambos vectores</returns>
		FORGE_API Vector3 cross(const Vector3& w) const;

		/// <summary>
		/// Calcula el producto escalar de V y W: v � w
		/// </summary>
		/// <param name="w">Segundo vector</param>
		/// <returns>Producto escalar de ambos vectores</returns>
		FORGE_API float dot(const Vector3& w) const;
		#pragma endregion

		#pragma region Setters
		/// <summary>
		/// Asigna un nuevo valor a la componente en X del vector
		/// </summary>
		/// <param name="_x">Nuevo valor en X</param>
		FORGE_API void setX(float newX);

		/// <summary>
		/// Asigna un nuevo valor a la componente en Y del vector
		/// </summary>
		/// <param name="_x">Nuevo valor en Y</param>
		FORGE_API void setY(float newY);

		/// <summary>
		/// Asigna un nuevo valor a la componente en Z del vector
		/// </summary>
		/// <param name="_x">Nuevo valor en Z</param>
		FORGE_API void setZ(float newZ);

		/// <summary>
		/// Asigna nuevos valores al vector
		/// </summary>
		/// <param name="_x">Valor del vector en el eje X</param>
		/// <param name="_y">Valor del vector en el eje Y</param>
		/// <param name="_z">Valor del vector en el eje Z</param>
		FORGE_API void set(float newX, float newY, float newZ);

		/// <summary>
		/// Copia un vector constante
		/// </summary>
		/// <param name="w">Vector a copiar</param>
		FORGE_API void set(const Vector3& w);

		/// <summary>
		/// Copia la referencia de un vector
		/// </summary>
		/// <param name="w">Vector a copiar</param>
		FORGE_API void set(const Vector3&& w);

		/// <summary>
		/// Copia un el contenido de un puntero a Vector3
		/// </summary>
		/// <param name="w">Vector a copiar</param>
		FORGE_API void set(const Vector3* w);
		#pragma endregion

		#pragma region Getters
		/// <summary>
		/// Acceso a la componente en X del vector
		/// </summary>
		/// <returns>Devuelve la componente en X</returns>
		FORGE_API float getX() const;

		/// <summary>
		/// Acceso a la componente en Z del vector
		/// </summary>
		/// <returns>Devuelve la componente en Z</returns>
		FORGE_API float getY() const;

		/// <summary>
		/// Acceso a la componente en Z del vector
		/// </summary>
		/// <returns>Devuelve la componente en Z</returns>
		FORGE_API float getZ() const;
		#pragma endregion

		#pragma region Conversiones
		/// <summary>
		/// Conversion implicita de forge::Vector3 a Ogre::Vector3
		/// </summary>
		operator Ogre::Vector3f() const;

		/// <summary>
		/// Constructor por copia de Ogre::Vector3
		/// </summary>
		/// <param name="w">Vector de Ogre a copiar</param>
		Vector3(const Ogre::Vector3f& w);
		
		/// <summary>
		/// Constructor por copia de referencia a R value de Ogre::Vector3
		/// </summary>
		/// <param name="w">Vector de Ogre a copiar</param>
		Vector3(Ogre::Vector3f&& w) noexcept;
		
		/// <summary>
		/// Asigna la informacion del Ogre::Vector3 W a este forge::Vector3
		/// </summary>
		/// <param name="w">Vector de Ogre a asignar</param>
		/// <returns>El vector actualizado</returns>
		Vector3& operator=(const Ogre::Vector3f& w);

		/// Conversion implicita de forge::Vector3 a irrklang::vec3df
		/// </summary>
		operator irrklang::vec3df() const;
		#pragma endregion

		#pragma region Constantes
		static const FORGE_API_VAR Vector3 ZERO;
		static const FORGE_API_VAR Vector3 RIGHT;
		static const FORGE_API_VAR Vector3 LEFT;
		static const FORGE_API_VAR Vector3 UP;
		static const FORGE_API_VAR Vector3 DOWN;
		static const FORGE_API_VAR Vector3 FORWARD;
		static const FORGE_API_VAR Vector3 BACK;
		static const FORGE_API_VAR Vector3 UNIT;
		#pragma endregion
	};
}
#endif
