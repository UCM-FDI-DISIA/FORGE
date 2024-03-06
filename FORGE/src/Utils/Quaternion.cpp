#include "Quaternion.h"
using namespace forge;

#define kEpsilon = 0.000001

#pragma region Constructores
Quaternion::Quaternion() : 
	x(0), 
	y(0), 
	z(0), 
	w(0) {}

Quaternion::Quaternion(float _x, float _y, float _z, float _w) {
	set(_x, _y, _z, _w);
}

Quaternion::Quaternion(const Quaternion& q) {
	x = q.x;
	y = q.y;
	z = q.z;
	w = q.w;
}

Quaternion::Quaternion(Quaternion&& q) noexcept {
	x = q.x;
	y = q.y;
	z = q.z;
	w = q.w;
}

Quaternion::Quaternion(const Quaternion* q) {
	x = q->x;
	y = q->y;
	z = q->z;
	w = q->w;
}

Quaternion::Quaternion(const Vector3& e) {
	float bank = e.getX();
	float pitch = e.getY();
	float heading = e.getZ();
	x = cosf(bank / 2) * cosf(pitch / 2) * cosf(heading / 2) + sinf(bank / 2) * sinf(pitch / 2) * sinf(heading / 2);
	y = sinf(bank / 2) * cosf(pitch / 2) * cosf(heading / 2) - cosf(bank / 2) * sinf(pitch / 2) * sinf(heading / 2);
	z = cosf(bank / 2) * sinf(pitch / 2) * cosf(heading / 2) + sinf(bank / 2) * cosf(pitch / 2) * sinf(heading / 2);
	w = cosf(bank / 2) * cosf(pitch / 2) * sinf(heading / 2) - sinf(bank / 2) * sinf(pitch / 2) * cosf(heading / 2);
}

Quaternion::~Quaternion() {}
#pragma endregion

#pragma region Operadores
Quaternion& Quaternion::operator=(const Quaternion& q) {
	x = q.x;
	y = q.y;
	z = q.z;
	w = q.w;
	return *this;
}

Quaternion& forge::Quaternion::operator=(const Vector3& e) {
	return *this = Quaternion(e);
}

float Quaternion::dot(const Quaternion& q) const{
	return x * q.x + y * q.y + z * q.z + w * q.w;
}

Quaternion Quaternion::operator*(const Quaternion& q) const {
	return Quaternion(w * q.x + x * q.w + y * q.z - z * q.y, 
		w * q.y + y * q.w +	z * q.x - x * q.z, 
		w * q.z + z * q.w + x * q.y - y * q.x,
		w * q.w - x * q.x - y * q.y - z * q.z);
}

Quaternion forge::Quaternion::operator*=(const Quaternion& q) {
	*this = (*this) * q;
	return *this;
}

Vector3 Quaternion::operator*(const Vector3& v) const {
	float num = x * 2.0f;
	float num2 = y * 2.0f;
	float num3 = z * 2.0f;
	float num4 = x * num;
	float num5 = y * num2;
	float num6 = z * num3;
	float num7 = x * num2;
	float num8 = x * num3;
	float num9 = y * num3;
	float num10 = w * num;
	float num11 = w * num2;
	float num12 = w * num3;

	float rX = (1.0f - (num5 + num6)) * v.getX() + (num7 - num12) * v.getY() + (num8 + num11) * v.getZ();
	float rY = (num7 + num12) * v.getX() + (1.0f - (num4 + num6)) * v.getY() + (num9 - num10) * v.getZ();
	float rZ = (num8 - num11) * v.getX() + (num9 + num10) * v.getY() + (1.0f - (num4 + num5)) * v.getZ();

	return Vector3(rX, rY, rZ);
}

bool Quaternion::operator==(const Quaternion& q) const{
	return x == q.x && y == q.y && z == q.z && w == q.w;
}

bool Quaternion::operator!=(const Quaternion& q) const{
	return x != q.x && y != q.y && z != q.z && w != q.w;
}
#pragma endregion

Vector3 Quaternion::toEuler() const{
	// Rotacion en Z, Y y X respectivamente
	float heading = 0, pitch = 0, bank = 0;

	// Calculo de heading
	float numerador = 2 * (x * y + z * w);
	float denominador = 1 - 2 * (y * y + z * z);
	float result = numerador / denominador;
	heading = atanf(result);

	// Calculo de pitch
	result = 2 * (x * z - w * y);
	pitch = asinf(result);

	// Calculo de bank
	numerador = 2 * (x * w + y * z);
	denominador = 1 - 2 * (z * z + w * w);
	result = numerador / denominador;
	bank = atanf(result);

	return Vector3(bank, pitch, heading);
}

#pragma region Setters
void Quaternion::setX(float newX) { 
	x = newX; 
}

void Quaternion::setY(float newY) { 
	y = newY; 
}

void Quaternion::setZ(float newZ) { 
	z = newZ; 
}

void Quaternion::setW(float newW) { 
	w = newW; 
}

void Quaternion::set(float newX, float newY, float newZ, float newW) {
	x = newX; 
	y = newY;
	z = newZ; 
	w = newW;
}

void Quaternion::set(const Quaternion& v) {
	x = v.x;
	y = v.y;
	z = v.z;
	w = v.w;
}

void Quaternion::set(const Quaternion&& v) {
	x = v.x;
	y = v.y;
	z = v.z;
	w = v.w;
}

void Quaternion::set(const Quaternion* v) {
	x = v->x;
	y = v->y;
	z = v->z;
	w = v->w;
}
#pragma endregion

#pragma region Getters
float Quaternion::getX() const { 
	return x; 
}

float Quaternion::getY() const { 
	return y;
}

float Quaternion::getZ() const { 
	return z; 
}

float Quaternion::getW() const { 
	return w; 
}
#pragma endregion

const Quaternion Quaternion::IDENTITY	(1, 1, 1, 0);