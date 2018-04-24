
#include "stdafx.h"
#include "Matrix.h"


Matrix2 Matrix2::operator *(const Matrix2 Other) const
{
	Matrix2 result;

	result._11 = _11 * Other._11 + _12 * Other._21;
	result._12 = _11 * Other._12 + _12 * Other._22;
	result._21 = _21 * Other._11 + _22 * Other._21;
	result._22 = _21 * Other._12 + _22 * Other._22;
	return result;
}

Matrix3 Matrix3::operator *(const Matrix3 Other) const
{
	Matrix3 result;

	result._11 = _11 * Other._11 + _12 * Other._21 + _13 * Other._31;
	result._12 = _11 * Other._12 + _12 * Other._22 + _13 * Other._32;
	result._13 = _11 * Other._13 + _12 * Other._23 + _13 * Other._33;
	result._21 = _21 * Other._11 + _22 * Other._21 + _23 * Other._31;
	result._22 = _21 * Other._12 + _22 * Other._22 + _23 * Other._32;
	result._23 = _21 * Other._13 + _22 * Other._23 + _23 * Other._33;
	result._31 = _31 * Other._11 + _32 * Other._21 + _33 * Other._31;
	result._32 = _31 * Other._12 + _32 * Other._22 + _33 * Other._32;
	result._33 = _31 * Other._13 + _32 * Other._23 + _33 * Other._33;
	return result;
}
