#pragma once

#include "stdafx.h"

struct Matrix2
{
public:
	float _11, _12;
	float _21, _22;

	Matrix2() {};
	Matrix2(float m11, float m12, float m21, float m22)
	{
		_11 = m11;
		_12 = m12;

		_21 = m21;
		_22 = m22;
	};

	void SetScale(float a, float b)
	{
		SetIdentity();
		_11 = a;
		_22 = b;
	}

	void SetIdentity()
	{
		_11 = 1.0f;
		_12 = 0.0f;

		_21 = 0.0f;
		_22 = 1.0f;
	};

	void SetRotation(float degree)
	{
		float radian = Deg2Rad(degree);
		_11 = cosf(radian);
		_12 = -sinf(radian);
		_21 = sinf(radian);
		_22 = cosf(radian);
	}

	Matrix2 operator *(const Matrix2 Other) const;
};

struct Matrix3
{
public:
	float _11, _12, _13;
	float _21, _22, _23;
	float _31, _32, _33;

	Matrix3() : _11(0), _12(0), _13(0), _21(0), _22(0), _23(0), _31(0), _32(0), _33(0)
	{
	};

	void SetTranslation(float InX, float InY)
	{
		SetIdentity();
		_13 = InX;
		_23 = InY;
	}

	void SetScale(float a)
	{
		SetIdentity();
		_11 = a;
		_22 = a;
	}

	void SetIdentity()
	{
		_11 = 1.0f;
		_12 = 0.0f;
		_13 = 0.0f;
		_21 = 0.0f;
		_22 = 1.0f;
		_23 = 0.0f;
		_31 = 0.0f;
		_32 = 0.0f;
		_33 = 1.0f;
	};

	void SetRotation(float degree)
	{
		SetIdentity();
		_11 = cosf(Deg2Rad(degree));
		_12 = -sinf(Deg2Rad(degree));
		_21 = -_12;
		_22 = _11;
	}

	Matrix3 operator *(const Matrix3 Other) const;
};