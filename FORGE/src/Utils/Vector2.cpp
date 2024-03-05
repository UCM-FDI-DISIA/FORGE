#include "Vector2.h"
#include <cmath>
using namespace forge;

Vector2::Vector2() :
	x(0.0f),
	y(0.0f) {
}
Vector2::Vector2(float _x, float _y) :
	x(_x),
	y(_y) {
}
Vector2::Vector2(const Vector2& v) :
	x(v.x),
	y(v.y) {
}

Vector2::~Vector2(){}

Vector2 Vector2::operator+(const Vector2& v) const {
	return Vector2(x + v.x, y + v.y);
}
Vector2 Vector2::operator-(const Vector2& v) const {
	return Vector2(x - v.x, y - v.y);
}
Vector2 Vector2::operator*(float e) const {
	return Vector2(x * e, y * e );
}
Vector2 Vector2::operator/(float e) const {
	return Vector2(x / e, y / e );
}
float Vector2::operator *(const Vector2& v) const {
	return (x * v.x + y * v.y);
}
bool Vector2::operator==(const Vector2& v) const {
	return (x == v.x && y == v.y);
}
bool Vector2::operator!=(const Vector2& v) const {
	return (x != v.x || y != v.y);
}

float Vector2::magnitude() const {
	return sqrtf(x * x + y * y);
}
Vector2 Vector2::normalize() const {
	return *this / magnitude();
}

float Vector2::getX() const { return x; }

float Vector2::getY() const { return y; }

void Vector2::setX(float _x) {	x = _x; }

void Vector2::setY(float _y) {	y = _y; }

void Vector2::set(const Vector2& v) {
	x = v.x;
	y = v.y;
}
void Vector2::set(float _x, float _y) {
	x = _x;
	y = _y;
}