#pragma once
#include "Vector3.h"
class Quaternion {
private:

protected:
	float x;
	float y;
	float z;
	float w;
public:
	Quaternion();
	Quaternion(float x, float y, float z, float w);
	Quaternion(const Quaternion& v);
	Quaternion(Quaternion&& v) noexcept;
	Quaternion(const Quaternion* v);
	~Quaternion();

	#pragma region Operadores
	// Copia
	Quaternion& operator=(const Quaternion& v);
	// Escalar
	float dot(const Quaternion& v) const;
	// 
	Quaternion operator*(const Quaternion& v) const;
	// 
	Vector3 operator*(const Vector3& v) const;
	// Iguales ?
	bool operator==(const Quaternion& v) const;
	// Distintos ?
	bool operator!=(const Quaternion& v) const;
	#pragma endregion


	#pragma region Setters
	// Setters
	void setX(float _x);
	void setY(float _y);
	void setZ(float _z);
	void setW(float _w);

	/// <summary>
	/// Asigna nuevos valores al vector
	/// </summary>
	/// <param name="_x">Valor del vector en el eje X</param>
	/// <param name="_y">Valor del vector en el eje Y</param>
	/// <param name="_z">Valor del vector en el eje Z</param>
	void set(float _x, float _y, float _z, float _w);
	void set(const Quaternion& v);
	void set(const Quaternion&& v);
	void set(const Quaternion* v);
	#pragma endregion

	#pragma region Getters
	// Getters
	float getX() const;
	float getY() const;
	float getZ() const;
	float getW() const;
	#pragma endregion
};