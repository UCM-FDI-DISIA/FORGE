#include "Vector4.h"
#include "imgui.h"
using namespace forge;
Vector4::Vector4(){}
Vector4::Vector4(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) {}
Vector4::Vector4(const Vector4& v) : x(v.x), y(v.y), z(v.z), w(v.w) {}
Vector4::~Vector4(){}

#pragma region Getters
float Vector4::getX() const {
	return x;
}
float Vector4::getY() const {
	return y;
}
float Vector4::getZ() const {
	return z;
}
float Vector4::getW() const {
	return w;
}
#pragma endregion

#pragma region Setters
void Vector4::setX(float x_) {
	x = x_;
}
void Vector4::setY(float y_)  {
	y = y_;
}
void Vector4::setZ(float z_)  {
	z = z_;
}
void Vector4::setW(float w_)  {
	w = w_;
}
void Vector4::set(const Vector4& v) {
	x = v.x;
	y = v.y;
	z = v.z;
	w = v.w;
}
void Vector4::set(float _x, float _y, float _z, float _w) {
	x = _x;
	y = _y;
	z = _z;
	w = _w;
}
#pragma endregion

#pragma region Conversiones
Vector4::operator ImVec4() const {
	return ImVec4(x, y, z, w);
}
#pragma endregion

