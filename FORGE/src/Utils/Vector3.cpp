#include "Vector3.h"
#include <btVector3.h>
#include <cmath>
#include <OgreVector3.h>
using namespace forge;

#define PI 3.14159265358979323846264338327950288
#define E 2.71828182845904523536

#pragma region Constructores
Vector3::Vector3() :
	x(0),
	y(0),
	z(0) {}

Vector3::Vector3(float _x, float _y, float _z) {
	set(_x, _y, _z);
}

Vector3::Vector3(float v) :
	x(v),
	y(v),
	z(v) {}

Vector3::Vector3(const Vector3& w) :
	x(w.x),
	y(w.y),
	z(w.z) {}

Vector3::Vector3(Vector3&& w) noexcept :
	x(w.x),
	y(w.y),
	z(w.z) {}

Vector3::Vector3(const Vector3* w) :
	x(w->x),
	y(w->y),
	z(w->z) {}

Vector3::~Vector3() {}
#pragma endregion

float Vector3::magnitude() const {
	return sqrt(x * x + y * y + z * z);
}

float Vector3::sqrMagnitude() const {
	return magnitude() * magnitude();
}

Vector3 Vector3::normalized() const{
	float m = magnitude();
	return Vector3(x / m, y / m, z / m);
}

Vector3* Vector3::normalize() {
	float m = magnitude();
	x /= m;
	y /= m;
	z /= m;
	return this;
}

float Vector3::distance(const Vector3& w) const {
	float m = Vector3(x - w.x, y - w.y, z - w.z).magnitude();
	return m;
}

Vector3 Vector3::maxV(const Vector3& w) const {
	return Vector3(std::fmaxf(x, w.x), std::fmaxf(y, w.y), std::fmaxf(z, w.z));
}

Vector3 Vector3::minV(const Vector3& w) const {
	return Vector3(std::fminf(x, w.x), std::fminf(y, w.y), std::fminf(z, w.z));
}

Vector3 Vector3::lerp(const Vector3& w, float t) const {
	return Vector3(x + (w.x - x) * t, y + (w.y - y) * t, z + (w.z - z) * t);
}

#pragma region Operadores
Vector3& Vector3::operator=(const Vector3& w) {
	x = w.x;
	y = w.y;
	z = w.z;
	return *this;
}

Vector3 Vector3::operator+(const Vector3& w)  const {
	return Vector3(x + w.x, y + w.y, z + w.z);
}

Vector3 Vector3::operator+=(const Vector3& w) {
	x += w.x;
	y += w.y;
	z += w.z;
	return *this;
}

Vector3 Vector3::operator-(const Vector3& w) const {
	return Vector3(x - w.x, y - w.y, z - w.z);
}

Vector3 Vector3::operator*(float d)  const {
	return Vector3(x * d, y * d, z * d);
}

Vector3 Vector3::operator/(float d)  const {
	return Vector3(x / d, y / d, z / d);
}

Vector3 Vector3::operator*(const Vector3& w)  const {
	return Vector3(x * w.x, y * w.y, z * w.z);
}

Vector3 Vector3::operator*=(const Vector3& w) {
	x *= w.x;
	y *= w.y;
	z *= w.z;
	return *this;
}

bool Vector3::operator==(const Vector3& w) const {
	double min = pow(1, E - 5);
	return (abs(x - w.x) <= min && abs(y - w.y) <= min && abs(z - w.z) <= min);
}

bool Vector3::operator!=(const Vector3& w)  const {
	double min = pow(1, E - 5);
	return (abs(x - w.x) > min && abs(y - w.y) > min && abs(z - w.z) > min);
}
#pragma endregion

#pragma region Angulos
double Vector3::angle(const Vector3& w) const {
	double prodEsc = dot(w);
	double angle = std::acos(prodEsc / (magnitude() * w.magnitude()));

	return angle * 180 / PI;
}

Vector3 Vector3::reflect(const Vector3& normal) const {
	Vector3 nNormalised = normal.normalized();
	float dotProduct = dot(nNormalised);
	Vector3 reflectPart = nNormalised * (2 * dotProduct);
	return Vector3(x, y, z) - reflectPart;
}

Vector3 Vector3::project(const Vector3& w) const {
	float dotProduct = dot(w);
	float div = dotProduct / w.sqrMagnitude();
	return w * div;
}

Vector3 Vector3::cross(const Vector3& w) const {
	float compX = y * w.z - z * w.y;
	float compY = x * w.z - z * w.x;
	float compZ = x * w.y - y * w.x;
	return Vector3(compX, -1.0f * compY, compZ);
}

float forge::Vector3::dot(const Vector3& w) const {
	return w.x * x + w.y * y + w.z * z;
}
#pragma endregion

#pragma region Setters
void Vector3::setX(float newX) { 
	x = newX;
}

void Vector3::setY(float newY) {
	y = newY;
}

void Vector3::setZ(float newZ) {
	z = newZ;
}

void Vector3::set(float newX, float newY, float newZ) {
	x = newX;
	y = newY;
	z = newZ;
}

void Vector3::set(const Vector3& w) {
	x = w.x;
	y = w.y;
	z = w.z;
}

void Vector3::set(const Vector3&& w) {
	x = w.x;
	y = w.y;
	z = w.z;
}

void Vector3::set(const Vector3* w) {
	x = w->x;
	y = w->y;
	z = w->z;
}
#pragma endregion

#pragma region Getters
float Vector3::getX() const { 
	return x; 
}

float Vector3::getY() const { 
	return y; 
}

float Vector3::getZ() const { 
	return z; 
}
#pragma endregion

#pragma region Conversiones
forge::Vector3::operator Ogre::Vector3f() const {
	return Ogre::Vector3f(x, y, z);
}

Vector3::Vector3(const Ogre::Vector3f& w) :
	x(w.x),
	y(w.y),
	z(w.z) {
}

Vector3::Vector3(Ogre::Vector3f&& w) noexcept :
	x(w.x),
	y(w.y),
	z(w.z) {
}

Vector3& Vector3::operator=(const Ogre::Vector3f& w) {
	x = w.x;
	y = w.y;
	z = w.z;
	return *this;
}

forge::Vector3::operator btVector3() const {
	return btVector3(x, y, z);
}

Vector3::Vector3(const btVector3& w) :
	x(w.getX()),
	y(w.getY()),
	z(w.getZ()) {}

Vector3::Vector3(btVector3&& w) noexcept :
	x(w.getX()),
	y(w.getY()),
	z(w.getZ()) {}

Vector3& Vector3::operator=(const btVector3& w) {
	x = w.getX();
	y = w.getY();
	z = w.getZ();
	return *this;
}
#pragma endregion

#pragma region Constantes
const Vector3 Vector3::ZERO		(0.0f, 0.0f, 0.0f);
const Vector3 Vector3::RIGHT	(1.0f, 0.0f, 0.0f);
const Vector3 Vector3::LEFT		(-1.0f, 0.0f, 0.0f);
const Vector3 Vector3::UP		(0.0f, 1.0f, 0.0f);
const Vector3 Vector3::DOWN		(0.0f, -1.0f, 0.0f);
const Vector3 Vector3::FORWARD	(0.0f, 0.0f, 1.0f);
const Vector3 Vector3::BACK		(0.0f, 0.0f, -1.0f);
const Vector3 Vector3::UNIT		(1.0f, 1.0f, 1.0f);
#pragma endregion