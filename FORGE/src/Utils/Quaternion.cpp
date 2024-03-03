#include "Quaternion.h"
using namespace forge;

#define kEpsilon = 0.000001

Quaternion::Quaternion() : x(0), y(0), z(0) {}

Quaternion::Quaternion(float _x, float _y, float _z, float _w) {
	set(_x, _y, _z, _w);
}

Quaternion::Quaternion(const Quaternion& v) : x(v.x), y(v.y), z(v.z) {}

Quaternion::Quaternion(Quaternion&& v) noexcept :
	x(v.x), y(v.y), z(v.z) {}

Quaternion::Quaternion(const Quaternion* v) :
	x(v->x), y(v->y), z(v->z) {}

Quaternion::~Quaternion() {}

#pragma region Operadores
Quaternion& Quaternion::operator=(const Quaternion& q) {

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

bool Quaternion::operator==(const Quaternion& q) const{
	return dot(q) > 0.999999f;
}

bool Quaternion::operator!=(const Quaternion& q) const{
	return dot(q) <= 0.999999f;
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
	Vector3 result = Vector3();
	float rX = (1.0f - (num5 + num6)) * v.getX() + (num7 - num12) * v.getY() + (num8 + num11) * v.getZ();
	float rY = (num7 + num12) * v.getX() + (1.0f - (num4 + num6)) * v.getY() + (num9 - num10) * v.getZ();
	float rZ = (num8 - num11) * v.getX() + (num9 + num10) * v.getY() + (1.0f - (num4 + num5)) * v.getZ();
	result.set(rX, rY, rZ);
	return result;
}
#pragma endregion


#pragma region Setters
void Quaternion::setX(float _x) { x = _x; }
void Quaternion::setY(float _y) { y = _y; }
void Quaternion::setZ(float _z) { z = _z; }
void Quaternion::setW(float _w) { w = _w; }

void Quaternion::set(float _x, float _y, float _z, float _w) {
	x = _x; y = _y; z = _z; w = _w;
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
float Quaternion::getX() const { return x; }
float Quaternion::getY() const { return y; }
float Quaternion::getZ() const { return z; }
float Quaternion::getW() const { return w; }
#pragma endregion