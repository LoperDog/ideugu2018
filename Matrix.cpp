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
