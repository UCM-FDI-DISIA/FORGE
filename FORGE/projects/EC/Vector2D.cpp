#include "Vector2D.h"
#include <cmath>

Vector2D::Vector2D() :
	X(0.0f),
	Y(0.0f) {
}
Vector2D::Vector2D(float x, float y) :
	X(x),
	Y(y) {
}
Vector2D::Vector2D(const Vector2D& v) :
	X(v.X),
	Y(v.Y) {
}

Vector2D::~Vector2D(){}

Vector2D Vector2D::operator+(const Vector2D& v) const {
	return Vector2D( X + v.X, Y + v.Y );
}
Vector2D Vector2D::operator-(const Vector2D& v) const {
	return Vector2D( X - v.X, Y - v.Y );
}
Vector2D Vector2D::operator*(float e) const {
	return Vector2D( X * e, Y * e );
}
Vector2D Vector2D::operator/(float e) const {
	return Vector2D( X / e, Y / e );
}
float Vector2D::operator *(const Vector2D& v) const {
	return ( X * v.X + Y * v.Y );
}
bool Vector2D::operator==(const Vector2D& v) const {
	return (X == v.X && Y == v.Y);
}
bool Vector2D::operator!=(const Vector2D& v) const {
	return (X != v.X || Y != v.Y);
}

float Vector2D::magnitude() const {
	return sqrtf( X*X + Y*Y );
}
Vector2D Vector2D::normalize() const {
	return *this / magnitude();
}

float Vector2D::getX() const{
	return X;
}

float Vector2D::getY() const{
	return Y;
}

void Vector2D::setX(float x) {
	X = x;
}
void Vector2D::setY(float y) {
	Y = y;
}
void Vector2D::set(const Vector2D& v) {
	X = v.X;
	Y = v.Y;
}
void Vector2D::set(float x, float y) {
	X = x;
	Y = y;
}