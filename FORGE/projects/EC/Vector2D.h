#pragma once
#ifndef VECTOR2D_H_
#define VECTOR2D_H_
class Vector2D {
private:
	// Primera coordenada
	float X;
	// Segunda coordenada
	float Y;
public:
	/// <summary>
	/// Constructora por defecto de la clase Vector2D
	/// </summary>	
	Vector2D();
	/// <summary>
	/// Constructora a partir de parametros
	/// </summary>	
	Vector2D(float x, float y);
	/// <summary>
	/// Constructora a partir de otro vector
	/// </summary>	
	Vector2D(const Vector2D& v);
	/// <summary>
	/// Destructora por defecto de la clase Vector2D
	/// </summary>
	~Vector2D();

	/// <summary>
	/// Suma dos vectores
	/// </summary>	
	Vector2D operator+(const Vector2D& v) const;
	/// <summary>
	/// Resta dos vectores
	/// </summary>	
	Vector2D operator-(const Vector2D& v) const;
	/// <summary>
	/// Multiplica un vector por un escalar
	/// </summary>	
	Vector2D operator*(float e) const;
	/// <summary>
	/// Divide un vector por un escalar
	/// </summary>
	Vector2D operator/(float e) const;
	/// <summary>
	/// Producto escalar
	/// </summary>
	float operator*(const Vector2D& v) const;
	/// <summary>
	/// Igualdad de dos vectores
	/// </summary>
	bool operator==(const Vector2D& v) const;
	/// <summary>
	/// Desigualdad de dos vectores
	/// </summary>
	bool operator!=(const Vector2D& v) const;

	/// <summary>
	/// Calcula el modulo de un vector
	/// </summary>
	float magnitude() const;
	/// <summary>
	/// Normaliza un vector
	/// </summary>
	Vector2D normalize() const;

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
	void setX(float x);
	/// <summary>
	/// Setea el valor de la coordenada y
	/// </summary>	
	void setY(float y);
	/// <summary>
	/// Setea un vector a través de otro vector
	/// </summary>	
	void set(const Vector2D& v);
	/// <summary>
	/// Setea un vector a través de floats
	/// </summary>	
	void set(float x, float y);
};
#endif

