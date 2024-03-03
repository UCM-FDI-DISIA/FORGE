#pragma once
#include <cmath>

class Vector3 {
private:
	float x;
	float y;
	float z;
protected:

public:
	Vector3();

	Vector3(float _x, float _y, float _z);

	Vector3(const Vector3& v);

	Vector3(Vector3&& v) noexcept;

	Vector3(const Vector3* v);

	~Vector3();

	/// <summary>
	/// Calcula la longitud del vector
	/// </summary>
	/// <returns>La longitud del vector</returns>
	float magnitude() const;

	float sqrMagnitude() const;

	/// <summary>
	/// Escala el vector para que tenga magnitud 1
	/// </summary>
	Vector3 normalised() const;

	

	// Metodos de uso
	float distance(const Vector3& v) const;
	Vector3 maxV(const Vector3& v) const;
	Vector3 minV(const Vector3& v) const;
	Vector3 Lerp(const Vector3& v, float t) const;

	#pragma region Operadores
	// Copia
	Vector3& operator=(const Vector3& v);
	// Suma
	Vector3 operator+(const Vector3& v) const;
	// Resta
	Vector3 operator-(const Vector3& v) const;
	// Multiplica por constante (escalado)
	Vector3 operator*(float d) const;
	// Division por constante (escalado)
	Vector3 operator/(float d) const;
	// Multiplicacion escalar
	float operator*(const Vector3& d) const;
	// Iguales ?
	bool operator==(const Vector3& v) const;
	// Distintos ?
	bool operator!=(const Vector3& v) const;
	#pragma endregion

	// Cosas de angulos
	float angle(const Vector3& v) const;
	Vector3 reflect(const Vector3& normal) const;
	Vector3 project(const Vector3& v);
	Vector3 cross(const Vector3& v) const;

	#pragma region Setters
	// Setters
	void setX(float _x);
	void setY(float _y);
	void setZ(float _z);

	/// <summary>
	/// Asigna nuevos valores al vector
	/// </summary>
	/// <param name="_x">Valor del vector en el eje X</param>
	/// <param name="_y">Valor del vector en el eje Y</param>
	/// <param name="_z">Valor del vector en el eje Z</param>
	void set(float _x, float _y, float _z);
	void set(const Vector3& v);
	void set(const Vector3&& v);
	void set(const Vector3* v);
	#pragma endregion

	#pragma region Getters
	// Getters
	float getX() const;
	float getY() const;
	float getZ() const;
	#pragma endregion
};