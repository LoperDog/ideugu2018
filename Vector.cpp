#include "stdafx.h"
#include "Vector.h"

float Vector2::Dist(const Vector2 &V1, const Vector2 &V2)
{
	return sqrtf(Vector2::DistSquared(V1, V2));
}

float Vector2::DistSquared(const Vector2 &V1, const Vector2 &V2)
{
	return (V2.X - V1.X) * (V2.X - V1.X) + (V2.Y - V1.Y) * (V2.Y - V1.Y);
}

Vector2 Vector2::operator*(Matrix2 Mat) const
{
	Vector2 result;
	result.X = X * Mat._11 + Y * Mat._12;
	result.Y = X * Mat._21 + Y * Mat._22;
	return result;
}


Vector3 Vector3::operator+(const Vector3& vec) const
{
	return Vector3((X + vec.X), (Y + vec.Y), (Z + vec.Z));
}

Vector3 Vector3::operator*(const float val) const
{

	return Vector3(X * val, Y * val, Z * val);
}



Vector3 Vector3::operator*(const Matrix3 & mat) const
{
	return Vector3(
		(mat._11 * X + mat._12 * X + mat._13 * X),
		(mat._21 * Y + mat._22 * Y + mat._23 * Y),
		(mat._31 * Z + mat._32 * Z + mat._33 * Z)
	);

}

Vector3 Vector3::operator=(const Vector2& vec) const
{
	return Vector3(vec.X, vec.Y, 1.0f);
}
