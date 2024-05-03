#include "Quaternion.h"
#include <cmath>
#pragma warning(push)
#pragma warning(disable : 26495)
#include <OgreQuaternion.h>
#include <btQuaternion.h>
#pragma warning(pop)
using namespace forge;

#define kEpsilon = 0.000001

#pragma region Constructores
Quaternion::Quaternion() : 
	x(0.0f), 
	y(0.0f), 
	z(0.0f),
	w(1.0f) {
}

Quaternion::Quaternion(float _x, float _y, float _z, float _w) :
	x(_x), 
	y(_y),
	z(_z),
	w(_w) {
}

Quaternion::Quaternion(Vector3 const& vec, float angle) {
	set(vec.getX(), vec.getY(), vec.getZ(), angle);
}

Quaternion::Quaternion(const Quaternion& q) :
	x(q.x),
	y(q.y),
	z(q.z),
	w(q.w) {
}

Quaternion::Quaternion(Quaternion&& q) noexcept : 
	x(q.x), 
	y(q.y), 
	z(q.z), 
	w(q.w) {
}

Quaternion::Quaternion(const Quaternion* q) : 
	x(q->x),
	y(q->y),
	z(q->z),
	w(q->w) {
}

Quaternion::Quaternion(const Vector3& e) {
	float bank = e.getX();
	float pitch = e.getY();
	float heading = e.getZ();
	w = cosf(bank / 2) * cosf(pitch / 2) * cosf(heading / 2) + sinf(bank / 2) * sinf(pitch / 2) * sinf(heading / 2);
	x = sinf(bank / 2) * cosf(pitch / 2) * cosf(heading / 2) - cosf(bank / 2) * sinf(pitch / 2) * sinf(heading / 2);
	y = cosf(bank / 2) * sinf(pitch / 2) * cosf(heading / 2) + sinf(bank / 2) * cosf(pitch / 2) * sinf(heading / 2);
	z = cosf(bank / 2) * cosf(pitch / 2) * sinf(heading / 2) - sinf(bank / 2) * sinf(pitch / 2) * cosf(heading / 2);	
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

float Quaternion::dot(const Quaternion& q) const {
	return x * q.x + y * q.y + z * q.z + w * q.w;
}

Quaternion Quaternion::operator*(const Quaternion& q) const {
	Quaternion p = Quaternion();
	p.w = w * q.w - x * q.x - y * q.y - z * q.z;
	p.x = w * q.x + x * q.w + y * q.z - z * q.y;
	p.y = w * q.y + y * q.w + z * q.x - x * q.z;
	p.z = w * q.z + z * q.w + x * q.y - y * q.x;
	p.normalize();
	return p;
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

bool Quaternion::operator==(const Quaternion& q) const {
	return x == q.x && y == q.y && z == q.z && w == q.w;
}

bool Quaternion::operator!=(const Quaternion& q) const {
	return x != q.x && y != q.y && z != q.z && w != q.w;
}
#pragma endregion

Vector3 Quaternion::toEuler() const {
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

void Quaternion::normalize() {
	float num = sqrt(x * x + y * y + z * z + w * w);
	x /= num;
	y /= num;
	z /= num;
	w /= num;
}

#pragma region Setters
void Quaternion::setX(float newX) {
	x = newX * sinf(acos(w));
}

void Quaternion::setY(float newY) {
	y = newY * sinf(acos(w));
}

void Quaternion::setZ(float newZ) {
	z = newZ * sinf(acos(w));
}

void forge::Quaternion::setAbsX(float newX) {
	x = newX;
}

void forge::Quaternion::setAbsY(float newY) {
	y = newY;
}

void forge::Quaternion::setAbsZ(float newZ) {
	z = newZ;
}

void Quaternion::setAngle(float newAngle) {
	float prevSin = sinf(acos(w));
	float newSin = sinf(newAngle / 2.0f);
	w = cosf(newAngle / 2.0f);
	x = (x / prevSin) * newSin;
	y = (y / prevSin) * newSin;
	z = (z / prevSin) * newSin;
}

void forge::Quaternion::setW(float newW) {
	w = newW;
}

void forge::Quaternion::lookTo(forge::Vector3 lookTo, forge::Vector3 pos) {
	forge::Vector3 forward = pos - lookTo;
	forward.normalize();
	forge::Vector3 right = forge::Vector3(0, 1, 0).cross(forward);
	right.normalize();
	forge::Vector3 up = forward.cross(right);
	up.normalize();
	float _w = 0;
	float _x = 0;
	float _y = 0;
	float _z = 0;

	float trace = right.getX() + up.getY() + forward.getZ(); // I removed + 1.0f; see discussion with Ethan
	if (trace > 0) {// I changed M_EPSILON to 0
		float s = 0.5f / sqrtf(trace + 1.0f);
		_w = 0.25f / s;
		_x = (up.getZ() - forward.getY()) * s;
		_y = (forward.getX() - right.getZ()) * s;
		_z = (right.getY() - up.getX()) * s;
	}
	else {
		if (right.getX() > up.getY() && right.getX() > forward.getZ()) {
			float s = 2.0f * sqrtf(1.0f + right.getX() + up.getY() + forward.getZ());
			_w = (up.getZ() - forward.getY()) / s;
			_x = 0.25f * s;
			_y = (up.getX()+ right.getY()) / s;
			_z = (forward.getX() + right.getZ()) / s;
		}
		else if (up.getY() > forward.getZ()) {
			float s = 2.0f * sqrtf(1.0f + up.getY() - right.getX() - forward.getZ());
			_w = (forward.getX() - right.getZ()) / s;
			_x = (up.getX() + right.getY()) / s;
			_y = 0.25f * s;
			_z = (forward.getY() + up.getZ()) / s;
		}
		else {
			float s = 2.0f * sqrtf(1.0f + forward.getZ() - right.getX() - up.getY());
			_w = (right.getY() - up.getX()) / s;
			_x = (forward.getX() + right.getZ()) / s;
			_y = (forward.getY() + up.getZ()) / s;
			_z = 0.25f * s;
		}
	}

	//float _w = sqrt(std::max(0.0f, 1 + right.getX() + up.getY() + forward.getZ())) / 2;
	//float _x = sqrt(std::max(0.0f, 1 + right.getX() - up.getY() - forward.getZ())) / 2;
	//float _y = sqrt(std::max(0.0f, 1 - right.getX() + up.getY() - forward.getZ())) / 2;
	//float _z = sqrt(std::max(0.0f, 1 - right.getX() - up.getY() + forward.getZ())) / 2;
	//_x = _copysign(_x, (forward.getY() - up.getZ()));
	//_y = _copysign(_y, (right.getZ() - forward.getX()));
	//_z = _copysign(_z, (up.getX() - right.getY()));
	x = _x;
	y = _y;
	z = _z;
	w = _w;
}

void Quaternion::set(float newX, float newY, float newZ, float newAngle) {
	float sinWHalf = sinf(newAngle / 2.0f);
	x = newX * sinWHalf;
	y = newY * sinWHalf;
	z = newZ * sinWHalf;
	w = cosf(newAngle / 2.0f);
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
	return x / sinf(acosf(w));
}

float Quaternion::getY() const {
	return y / sinf(acosf(w));
}

float Quaternion::getZ() const {
	return z / sinf(acosf(w));
}

float forge::Quaternion::getAbsX() const {
	return x;
}

float forge::Quaternion::getAbsY() const {
	return y;
}

float forge::Quaternion::getAbsZ() const {
	return z;
}

float Quaternion::getAngle() const {
	return acosf(w) * 2.0f; 
}
FORGE_API float forge::Quaternion::getW() const {
	return w;
}
#pragma endregion

#pragma region Conversiones
Quaternion::operator Ogre::Quaternion() const {
	return Ogre::Quaternion(w, x, y, z);
}

Quaternion::Quaternion(const Ogre::Quaternion& q) : 
	x(q.x),
	y(q.y),
	z(q.z),
	w(q.w) {
}

Quaternion::Quaternion(Ogre::Quaternion&& q) noexcept :
	x(q.x),
	y(q.y),
	z(q.z),
	w(q.w) {
}

Quaternion& Quaternion::operator=(const Ogre::Quaternion& q) {
	x = q.x;
	y = q.y;
	z = q.z;
	w = q.w;
	return (*this);
}
#pragma endregion

const Quaternion Quaternion::IDENTITY	(0.0f, 0.0f, 0.0f, 1.0f);