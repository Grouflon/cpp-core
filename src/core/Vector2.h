#pragma once

#include "core/Serializable.h"

template <typename T>
class Vector2_t : public Serializable
{
public:
	Vector2_t();
	Vector2_t(T x, T y);
	Vector2_t(const Vector2_t&);
	virtual ~Vector2_t();

	Vector2_t& add(const Vector2_t&);
	Vector2_t& subtract(const Vector2_t&);
	Vector2_t& multiply(const Vector2_t&);
	Vector2_t& multiply(float);
	Vector2_t& divide(const Vector2_t&);
	Vector2_t& divide(float);

	Vector2_t& normalize();

	float cross(const Vector2_t&) const;
	float dot(const Vector2_t&) const;

	T* data();
	const T* data() const;

	Vector2_t getNormalized() const;
	Vector2_t getLengthSquared() const;
	Vector2_t getLength() const;
	float getAngle() const;

	Vector2_t& operator=(const Vector2_t&);
	Vector2_t operator+(const Vector2_t&);
	Vector2_t operator-(const Vector2_t&);
	Vector2_t operator*(const Vector2_t&);
	Vector2_t operator*(float);
	Vector2_t operator/(const Vector2_t&);
	Vector2_t operator/(float);

	Vector2_t& operator+=(const Vector2_t&);
	Vector2_t& operator-=(const Vector2_t&);
	Vector2_t& operator*=(const Vector2_t&);
	Vector2_t& operator*=(float);
	Vector2_t& operator/=(const Vector2_t&);
	Vector2_t& operator/=(float);

	virtual void serialize(Serializer*) override;

	T x;
	T y;
};

#include "core/Vector2.inl"

typedef Vector2_t<float>		Vector2;
typedef Vector2_t<int>			Vector2i;
typedef Vector2_t<unsigned int>	Vector2u;
typedef Vector2_t<float>		Vector2f;
typedef Vector2_t<double>		Vector2d;
