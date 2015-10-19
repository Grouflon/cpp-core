#pragma once

#include "core/Serializable.h"

// TODO-THINK: Should Math structures inherit Serializable or should Serializer force implentation of Math structures serialization ?
template <typename T>
class Vector3_t : public Serializable
{
public:
	Vector3_t();
	Vector3_t(T x, T y, T z);
	Vector3_t(const Vector3_t&);
	virtual ~Vector3_t();

	Vector3_t& add(const Vector3_t&);
	Vector3_t& subtract(const Vector3_t&);
	Vector3_t& multiply(const Vector3_t&);
	Vector3_t& multiply(float);
	Vector3_t& divide(const Vector3_t&);
	Vector3_t& divide(float);

	Vector3_t& normalize();

	Vector3_t cross(const Vector3_t&) const;
	float dot(const Vector3_t&) const;

	T* data();
	const T* data() const;

	Vector3_t getNormalized() const;
	Vector3_t getLengthSquared() const;
	Vector3_t getLength() const;

	Vector3_t& operator=(const Vector3_t&);
	Vector3_t operator+(const Vector3_t&);
	Vector3_t operator-(const Vector3_t&);
	Vector3_t operator*(const Vector3_t&);
	Vector3_t operator*(float);
	Vector3_t operator/(const Vector3_t&);
	Vector3_t operator/(float);

	Vector3_t& operator+=(const Vector3_t&);
	Vector3_t& operator-=(const Vector3_t&);
	Vector3_t& operator*=(const Vector3_t&);
	Vector3_t& operator*=(float);
	Vector3_t& operator/=(const Vector3_t&);
	Vector3_t& operator/=(float);

	virtual void serialize(Serializer*) override;

	T x;
	T y;
	T z;
};

#include "core/Vector3.inl"

typedef Vector3_t<float>		Vector3;
typedef Vector3_t<int>			Vector3i;
typedef Vector3_t<unsigned int>	Vector3u;
typedef Vector3_t<float>		Vector3f;
typedef Vector3_t<double>		Vector3d;
