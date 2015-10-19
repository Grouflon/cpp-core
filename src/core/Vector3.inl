#include <cmath>

#include "core/Serializer.h"

template <typename T>
Vector3_t<T>::Vector3_t()
	: x(0)
	, y(0)
{
}

template <typename T>
Vector3_t<T>::Vector3_t(T x, T y, T z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

template <typename T>
Vector3_t<T>::Vector3_t(const Vector3_t& other)
{
	x = other.x;
	y = other.y;
	z = other.z;
}

template <typename T>
Vector3_t<T>::~Vector3_t()
{
}

template <typename T>
Vector3_t<T>& Vector3_t<T>::add(const Vector3_t& other)
{
	x += other.x;
	y += other.y;
	z += other.z;
	return *this;
}

template <typename T>
Vector3_t<T>& Vector3_t<T>::subtract(const Vector3_t& other)
{
	x -= other.x;
	y -= other.y;
	z -= other.z;
	return *this;
}

template <typename T>
Vector3_t<T>& Vector3_t<T>::multiply(const Vector3_t& other)
{
	x *= other.x;
	y *= other.y;
	z *= other.z;
	return *this;
}

template <typename T>
Vector3_t<T>& Vector3_t<T>::multiply(float f)
{
	x *= f;
	y *= f;
	z *= f;
	return *this;
}

template <typename T>
Vector3_t<T>& Vector3_t<T>::divide(const Vector3_t& other)
{
	x /= other.x;
	y /= other.y;
	z /= other.z;
	return *this;
}

template <typename T>
Vector3_t<T>& Vector3_t<T>::divide(float f)
{
	x /= f;
	y /= f;
	z /= f;
	return *this;
}

template <typename T>
Vector3_t<T>& Vector3_t<T>::normalize()
{
	float length = getLength();
	x /= length;
	y /= length;
	z /= length;
	return *this;
}

template <typename T>
Vector3_t<T> Vector3_t<T>::cross(const Vector3_t& other) const
{
	return Vector3_t<T>(
		y*other.z - z*other.y,
		z*other.x - x*other.z,
		x*other.y - y*other.x
	);
}

template <typename T>
float Vector3_t<T>::dot(const Vector3_t& other) const
{
	return x*other.x + y*other.y + z*other.z;
}

template <typename T>
T* Vector3_t<T>::data()
{
	return &x;
}

template <typename T>
const T* Vector3_t<T>::data() const
{
	return &x;
}


template <typename T>
Vector3_t<T> Vector3_t<T>::getNormalized() const
{
	return *this / getLength();
}

template <typename T>
Vector3_t<T> Vector3_t<T>::getLengthSquared() const
{
	return x*x + y*y + z*z;
}

template <typename T>
Vector3_t<T> Vector3_t<T>::getLength() const
{
	return sqrt(getLengthSquared());
}

template <typename T>
Vector3_t<T>& Vector3_t<T>::operator=(const Vector3_t& other)
{
	x = other.x;
	y = other.y;
	z = other.z;
	return *this;
}

template <typename T>
Vector3_t<T> Vector3_t<T>::operator+(const Vector3_t& other)
{
	return Vector3_t<T>(x + other.x, y + other.y, z + other.z);
}

template <typename T>
Vector3_t<T> Vector3_t<T>::operator-(const Vector3_t& other)
{
	return Vector3_t<T>(x - other.x, y - other.y, z - other.z);
}

template <typename T>
Vector3_t<T> Vector3_t<T>::operator*(const Vector3_t& other)
{
	return Vector3_t<T>(x * other.x, y * other.y, z * other.z);
}

template <typename T>
Vector3_t<T> Vector3_t<T>::operator*(float f)
{
	return Vector3_t<T>(x * f, y * f, z * f);
}

template <typename T>
Vector3_t<T> Vector3_t<T>::operator/(const Vector3_t& other)
{
	return Vector3_t<T>(x / other.x, y / other.y, z / other.z);
}

template <typename T>
Vector3_t<T> Vector3_t<T>::operator/(float f)
{
	return Vector3_t<T>(x / f, y / f, z / f);
}

template <typename T>
Vector3_t<T>& Vector3_t<T>::operator+=(const Vector3_t& other)
{
	return add(other);
}

template <typename T>
Vector3_t<T>& Vector3_t<T>::operator-=(const Vector3_t& other)
{
	return subtract(other);
}

template <typename T>
Vector3_t<T>& Vector3_t<T>::operator*=(const Vector3_t& other)
{
	return multiply(other);
}

template <typename T>
Vector3_t<T>& Vector3_t<T>::operator*=(float f)
{
	return multiply(f);
}

template <typename T>
Vector3_t<T>& Vector3_t<T>::operator/=(const Vector3_t& other)
{
	return divide(other);
}

template <typename T>
Vector3_t<T>& Vector3_t<T>::operator/=(float f)
{
	return divide(f);
}

template <typename T>
void Vector3_t<T>::serialize(Serializer* serializer)
{
	serializer->serialize("x", x);
	serializer->serialize("y", y);
	serializer->serialize("z", z);
}