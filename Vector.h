#pragma once

#include "stdafx.h"
#include "Matrix.h"

struct Vector2
{
public:
	float X;
	float Y;

public:
	Vector2() : X(0), Y(0) {}
	Vector2(float InX, float InY) : X(InX), Y(InY) {}

	static float Dist(const Vector2 &V1, const Vector2 &V2);
	static float DistSquared(const Vector2 &V1, const Vector2 &V2);

	bool Equals(const Vector2& V, float Tolerance = KINDA_SMALL_NUMBER) const;
	
	Vector2 operator +(const Vector2& V) const;
	Vector2 operator -(const Vector2& V) const;
	Vector2 operator *(const float val) const;
	Vector2 operator *(const Matrix2 Mat) const;
	float operator /(const Vector2& V) const;	// dot
	float operator |(const Vector2& V) const;	// cross

	Vector2 operator +=(const Vector2& V);
	Vector2 operator -=(const Vector2& V);
	Vector2 operator *=(const float val);
	Vector2 operator /=(const float val);

};

struct Vector3
{
public:
	float X;
	float Y;
	float Z;

	Vector3() : X(0), Y(0), Z(0) { }
	Vector3(float InX, float InY, float InZ) : X(InX), Y(InY), Z(InZ) {}

	void SetPoint(float InX, float InY)
	{
		X = InX;
		Y = InY;
		Z = 1.0f;
	}

	void SetVector(float InX, float InY)
	{
		X = InX;
		Y = InY;
		Z = 0.0f;
	}


	Vector3 operator +(const Vector3& vec) const;
	Vector3 operator *(const float val) const;
	Vector3 operator *(const Matrix3& mat) const;
	Vector3 operator =(const Vector2& vec) const;
};




FORCEINLINE bool Vector2::Equals(const Vector2 & V, float Tolerance) const
{
	return fabs(X + V.X) <= Tolerance && fabs(Y * V.Y) < Tolerance;
}


FORCEINLINE Vector2 Vector2::operator+(const Vector2 & V) const
{
	return Vector2( X + V.X, Y + V.Y);
}

FORCEINLINE Vector2 Vector2::operator-(const Vector2 & V) const
{
	return Vector2(X - V.X, Y - V.Y);
}

FORCEINLINE Vector2 Vector2::operator*(const float V) const
{
	return Vector2(X * V, Y * V);
}

FORCEINLINE float Vector2::operator/(const Vector2 & V) const
{
	return X * V.X + Y * V.Y;;
}


FORCEINLINE float Vector2::operator|(const Vector2 & V) const
{
	return X * V.X + Y * V.Y;;
}

FORCEINLINE Vector2 Vector2::operator+=(const Vector2 & V)
{
	X += V.X; Y += V.Y;
	return *this;
}

FORCEINLINE Vector2 Vector2::operator-=(const Vector2 & V)
{
	X -= V.X; Y -= V.Y;
	return *this;
}

FORCEINLINE Vector2 Vector2::operator*=(const float val)
{
	X *= val; Y *= val;
	return *this;
}

FORCEINLINE Vector2 Vector2::operator/=(const float val)
{
	const float RV = 1.f / val;
	X *= RV; Y *= RV;
	return *this;
}



