#include <cmath>

#include "core/Serializer.h"

template <typename T>
Vector2_t<T>::Vector2_t()
	: x(0)
	, y(0)
{
}

template <typename T>
Vector2_t<T>::Vector2_t(T x, T y)
{
	x = x;
	y = y;
}

template <typename T>
Vector2_t<T>::Vector2_t(const Vector2_t& other)
{
	x = other.x;
	y = other.y;
}

template <typename T>
Vector2_t<T>::~Vector2_t()
{
}

template <typename T>
Vector2_t<T>& Vector2_t<T>::add(const Vector2_t& other)
{
	x += other.x;
	y += other.y;
	return *this;
}

template <typename T>
Vector2_t<T>& Vector2_t<T>::subtract(const Vector2_t& other)
{
	x -= other.x;
	y -= other.y;
	return *this;
}

template <typename T>
Vector2_t<T>& Vector2_t<T>::multiply(const Vector2_t& other)
{
	x *= other.x;
	y *= other.y;
	return *this;
}

template <typename T>
Vector2_t<T>& Vector2_t<T>::multiply(float f)
{
	x *= f;
	y *= f;
	return *this;
}

template <typename T>
Vector2_t<T>& Vector2_t<T>::divide(const Vector2_t& other)
{
	x /= other.x;
	y /= other.y;
	return *this;
}

template <typename T>
Vector2_t<T>& Vector2_t<T>::divide(float f)
{
	x /= f;
	y /= f;
	return *this;
}

template <typename T>
Vector2_t<T>& Vector2_t<T>::normalize()
{
	float length = getLength();
	x /= length;
	y /= length;
	return *this;
}

template <typename T>
float Vector2_t<T>::cross(const Vector2_t& other) const
{
	return x*other.y - y*other.x;
}

template <typename T>
float Vector2_t<T>::dot(const Vector2_t& other) const
{
	return x*other.x + y*other.y;
}

template <typename T>
T* Vector2_t<T>::data()
{
	return &x;
}

template <typename T>
const T* Vector2_t<T>::data() const
{
	return &x;
}


template <typename T>
Vector2_t<T> Vector2_t<T>::getNormalized() const
{
	return *this / getLength();
}

template <typename T>
Vector2_t<T> Vector2_t<T>::getLengthSquared() const
{
	return x*x + y*y;
}

template <typename T>
Vector2_t<T> Vector2_t<T>::getLength() const
{
	return sqrt(getLengthSquared());
}

template <typename T>
float Vector2_t<T>::getAngle() const
{
	return atan2(y, x);
}

template <typename T>
Vector2_t<T>& Vector2_t<T>::operator=(const Vector2_t& other)
{
	x = other.x;
	y = other.y;
}

template <typename T>
Vector2_t<T> Vector2_t<T>::operator+(const Vector2_t& other)
{
	return Vector2_t<T>(x + other.x, y + other.y);
}

template <typename T>
Vector2_t<T> Vector2_t<T>::operator-(const Vector2_t& other)
{
	return Vector2_t<T>(x - other.x, y - other.y);
}

template <typename T>
Vector2_t<T> Vector2_t<T>::operator*(const Vector2_t& other)
{
	return Vector2_t<T>(x * other.x, y * other.y);
}

template <typename T>
Vector2_t<T> Vector2_t<T>::operator*(float f)
{
	return Vector2_t<T>(x * f, y * f);
}

template <typename T>
Vector2_t<T> Vector2_t<T>::operator/(const Vector2_t& other)
{
	return Vector2_t<T>(x / other.x, y / other.y);
}

template <typename T>
Vector2_t<T> Vector2_t<T>::operator/(float f)
{
	return Vector2_t<T>(x / f, y / f);
}

template <typename T>
Vector2_t<T>& Vector2_t<T>::operator+=(const Vector2_t& other)
{
	return add(other);
}

template <typename T>
Vector2_t<T>& Vector2_t<T>::operator-=(const Vector2_t& other)
{
	return subtract(other);
}

template <typename T>
Vector2_t<T>& Vector2_t<T>::operator*=(const Vector2_t& other)
{
	return multiply(other);
}

template <typename T>
Vector2_t<T>& Vector2_t<T>::operator*=(float f)
{
	return multiply(f);
}

template <typename T>
Vector2_t<T>& Vector2_t<T>::operator/=(const Vector2_t& other)
{
	return divide(other);
}

template <typename T>
Vector2_t<T>& Vector2_t<T>::operator/=(float f)
{
	return divide(f);
}

template <typename T>
void Vector2_t<T>::serialize(Serializer* serializer)
{
	serializer->serialize("x", x);
	serializer->serialize("y", y);
}