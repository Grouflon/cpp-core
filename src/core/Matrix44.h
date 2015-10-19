#pragma once

#include "core/Serializable.h"

template <typename T> class Vector3_t;

// TODO-THINK: Should Math structures inherit Serializable or should Serializer force implentation of Math structures serialization ?
template <typename T>
class Matrix44_t : public Serializable
{
public:
	Matrix44_t();
	Matrix44_t(
		T s00, T s01, T s02, T s03,
		T s10, T s11, T s12, T s13,
		T s20, T s21, T s22, T s23,
		T s30, T s31, T s32, T s33
	);
	Matrix44_t(const Matrix44_t&);
	virtual ~Matrix44_t();

	void invert();

	Matrix44_t getInverse() const;

	Matrix44_t& operator=(const Matrix44_t&);
	Matrix44_t operator+(const Matrix44_t&);
	Matrix44_t operator-(const Matrix44_t&);
	Matrix44_t operator*(const Matrix44_t&);
	Matrix44_t operator*(float);
	Matrix44_t operator/(const Matrix44_t&);
	Matrix44_t operator/(float);

	Matrix44_t& operator+=(const Matrix44_t&);
	Matrix44_t& operator-=(const Matrix44_t&);
	Matrix44_t& operator*=(const Matrix44_t&);
	Matrix44_t& operator*=(float);
	Matrix44_t& operator/=(const Matrix44_t&);
	Matrix44_t& operator/=(float);

	virtual void serialize(Serializer*) override;

	static Matrix44_t translation(T x, T y, T z);
	static Matrix44_t translation(const Vector3_t<T>&);

	T values[16];
};

#include "core/Matrix44.inl"

typedef Matrix44_t<float>		Matrix44;
typedef Matrix44_t<float>		Matrix44f;
typedef Matrix44_t<double>		Matrix44d;
