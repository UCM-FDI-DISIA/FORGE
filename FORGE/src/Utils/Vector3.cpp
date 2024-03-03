#include "Vector3.h"
using namespace forge;

#define PI 3.14159265358979323846264338327950288
#define E 2.71828182845904523536

Vector3::Vector3() : 
	x(0), 
	y(0), 
	z(0) { 
}

Vector3::Vector3(float _x, float _y, float _z) {
	set(_x, _y, _z);
}

Vector3::Vector3(float v) : 
	x(v), 
	y(v), 
	z(v) {
}

Vector3::Vector3(const Vector3& v) : 
	x(v.x), 
	y(v.y), 
	z(v.z) { 
}

Vector3::Vector3(Vector3&& v) noexcept :
	x(v.x), 
	y(v.y), 
	z(v.z) { 
}

Vector3::Vector3(const Vector3* v) :
	x(v->x),
	y(v->y), 
	z(v->z) {
}

Vector3::~Vector3() {}

float Vector3::magnitude() const {
	return sqrt(x * x + y * y + z * z);
}

float Vector3::sqrMagnitude() const {
	return magnitude() * magnitude();
}

Vector3 Vector3::normalised() const{
	float m = magnitude();
	return Vector3(x / m, y / m, z / m);
}



float Vector3::distance(const Vector3& v) const {
	float m = Vector3(x - v.x, y - v.y, z - v.z).magnitude();
	return m;
}

Vector3 Vector3::maxV(const Vector3& v) const {
	return Vector3(std::fmaxf(x, v.x), std::fmaxf(y, v.y), std::fmaxf(z, v.z));
}

Vector3 Vector3::minV(const Vector3& v) const {
	return Vector3(std::fminf(x, v.x), std::fminf(y, v.y), std::fminf(z, v.z));
}

Vector3 Vector3::lerp(const Vector3& v, float t) const {
	return Vector3(x + (v.x - x) * t, y + (v.y - y) * t, z + (v.z - z) * t);
}

#pragma region Operadores
Vector3& Vector3::operator=(const Vector3& v) {
	x = v.x;
	y = v.y;
	z = v.z;
	return *this;
}

Vector3 Vector3::operator-(const Vector3& v) const {
	return Vector3(x - v.x, y - v.y, z - v.z);
}

Vector3 Vector3::operator+(const Vector3& v)  const {
	return Vector3(x + v.x, y + v.y, z + v.z);
}

Vector3 Vector3::operator+=(const Vector3& v) {
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}

Vector3 Vector3::operator*(float d)  const {
	return Vector3(x * d, y * d, z * d);
}

Vector3 Vector3::operator/(float d)  const {
	return Vector3(x / d, y / d, z / d);
}

Vector3 Vector3::operator*(const Vector3& v)  const {
	return Vector3(x*v.x, y*v.y, z * v.z);
}

Vector3 Vector3::operator*=(const Vector3& v) {
	x *= v.x;
	y *= v.y;
	z *= v.z;
	return *this;
}

bool Vector3::operator==(const Vector3& v) const {
	float m1 = magnitude();
	float m2 = v.magnitude();
	float min = pow(1, E - 5);
	return (abs(m1 - m2) <= min);
}

bool Vector3::operator!=(const Vector3& v)  const {
	Vector3 diff = Vector3(x, y, z) - v;
	float min = 1 * pow(10, -5);
	return (abs(diff.magnitude()) <= min);
}
#pragma endregion


float Vector3::angle(const Vector3& v) const {
	float prodEsc = dot(v);
	float angle = std::acos(prodEsc / (magnitude() * v.magnitude()));

	return angle * 180 / PI;
}

Vector3 Vector3::reflect(const Vector3& normal) const {
	Vector3 nNormalised = normal.normalised();
	float dotProduct = dot(nNormalised);
	Vector3 reflectPart = nNormalised * (2 * dotProduct);
	return Vector3(x,y,z) - reflectPart;
}

Vector3 Vector3::project(const Vector3& v) {
	float dotProduct = dot(v);
	float div = dotProduct / v.sqrMagnitude();
	return v * div;
}

Vector3 Vector3::cross(const Vector3& v) const {
	float compX = y * v.z - z * v.y;
	float compY = x * v.z - z * v.x;
	float compZ = x * v.y - y * v.x;
	return Vector3(compX, -1.0f * compY, compZ);
}

float forge::Vector3::dot(const Vector3& v) const {
	return v.x * x + v.y * y + v.z * z;
}

#pragma region Setters
void Vector3::setX(float _x) { x = _x; }
void Vector3::setY(float _y) { y = _y; }
void Vector3::setZ(float _z) { z = _z; }

void Vector3::set(float _x, float _y, float _z) {
	x = _x; y = _y; z = _z;
}

void Vector3::set(const Vector3& v) {
	x = v.x;
	y = v.y;
	z = v.z;
}

void Vector3::set(const Vector3&& v) {
	x = v.x;
	y = v.y;
	z = v.z;
}

void Vector3::set(const Vector3* v) {
	x = v->x;
	y = v->y;
	z = v->z;
}
#pragma endregion

#pragma region Getters
float Vector3::getX() const { return x; }
float Vector3::getY() const { return y; }
float Vector3::getZ() const { return z; }
#pragma endregion

#pragma region Constantes
const Vector3 Vector3::ZERO		(0.0f,0.0f,0.0f);
const Vector3 Vector3::RIGHT	(1.0f, 0.0f, 0.0f);
const Vector3 Vector3::LEFT		(-1.0f, 0.0f, 0.0f);
const Vector3 Vector3::UP		(0.0f, 1.0f, 0.0f);
const Vector3 Vector3::DOWN		(0.0f, -1.0f, 0.0f);
const Vector3 Vector3::FORWARD	(0.0f, 0.0f, 1.0f);
const Vector3 Vector3::BACK		(0.0f, 0.0f, -1.0f);
const Vector3 Vector3::UNIT		(1.0f, 1.0f, 1.0f);
#pragma endregion