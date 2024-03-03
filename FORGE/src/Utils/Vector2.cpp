#include "Vector2.h"
#include <cmath>
using namespace forge;

Vector2::Vector2() :
	X(0.0f),
	Y(0.0f) {
}
Vector2::Vector2(float x, float y) :
	X(x),
	Y(y) {
}
Vector2::Vector2(const Vector2& v) :
	X(v.X),
	Y(v.Y) {
}

Vector2::~Vector2(){}

Vector2 Vector2::operator+(const Vector2& v) const {
	return Vector2( X + v.X, Y + v.Y );
}
Vector2 Vector2::operator-(const Vector2& v) const {
	return Vector2( X - v.X, Y - v.Y );
}
Vector2 Vector2::operator*(float e) const {
	return Vector2( X * e, Y * e );
}
Vector2 Vector2::operator/(float e) const {
	return Vector2( X / e, Y / e );
}
float Vector2::operator *(const Vector2& v) const {
	return ( X * v.X + Y * v.Y );
}
bool Vector2::operator==(const Vector2& v) const {
	return (X == v.X && Y == v.Y);
}
bool Vector2::operator!=(const Vector2& v) const {
	return (X != v.X || Y != v.Y);
}

float Vector2::magnitude() const {
	return sqrtf( X*X + Y*Y );
}
Vector2 Vector2::normalize() const {
	return *this / magnitude();
}

float Vector2::getX() const{
	return X;
}

float Vector2::getY() const{
	return Y;
}

void Vector2::setX(float x) {
	X = x;
}
void Vector2::setY(float y) {
	Y = y;
}
void Vector2::set(const Vector2& v) {
	X = v.X;
	Y = v.Y;
}
void Vector2::set(float x, float y) {
	X = x;
	Y = y;
}