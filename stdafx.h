// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <windows.h>

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <math.h>
#include <intrin.h>

// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
#define PI 3.141592f
#define KINDA_SMALL_NUMBER 1.e-4f
#define FORCEINLINE __forceinline
#define RGBA32(r,g,b,a) ((ULONG)((BYTE)(b)) | (ULONG)(((BYTE)(g)) << 8) | (ULONG)(((BYTE)(r)) << 16) | (ULONG)(((BYTE)(a)) << 24))
#define RGB32(r,g,b) RGBA32(r, g, b, 255)

FORCEINLINE float Deg2Rad(float degree)
{
	return degree * PI / 180.0f;
}

FORCEINLINE int RoundToInt(float F)
{
	// Note: the x2 is to workaround the rounding-to-nearest-even-number issue when the fraction is .5
	return _mm_cvt_ss2si(_mm_set_ss(F + F + 0.5f)) >> 1;
}
