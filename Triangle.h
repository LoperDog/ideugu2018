#pragma once

#include "stdafx.h"
#include "Vector.h"

struct VertInOut
{
	VertInOut() {}
	VertInOut(Vector3 v, Vector2 u, ULONG c) : position(v), uv(u), color(c) {};

	Vector3 position;
	Vector2 uv;
	ULONG color;
};

struct FragIn
{
	FragIn() {};
	FragIn(Vector2 u, ULONG c) : uv(u), color(c) {};

	Vector2 uv;
	ULONG color;
};

struct Triangle
{
public:
	Triangle() {}
	Triangle(VertInOut v1, VertInOut v2, VertInOut v3)
	{
		vt[0] = v1;
		vt[1] = v2;
		vt[2] = v3;

		Vector2 sbbMin = Vector2(INFINITY, INFINITY);
		Vector2 sbbMax = Vector2(-INFINITY, -INFINITY);

		for (int i = 0; i < 3; i++)
		{
			Vector3 t = vt[i].position;
			if (t.X < sbbMin.X) sbbMin.X = t.X;
			if (t.Y < sbbMin.Y) sbbMin.Y = t.Y;
			if (t.X > sbbMax.X) sbbMax.X = t.X;
			if (t.Y > sbbMax.Y) sbbMax.Y = t.Y;
		}

		u = (vt[1].position - vt[0].position).ToVector2();
		v = (vt[2].position - vt[0].position).ToVector2();
		dotUU = u.Dot(u);
		dotUV = u.Dot(v);
		dotVV = v.Dot(v);
		invDenom = 1.0f / (dotUU * dotVV - dotUV * dotUV);

		Min.X = RoundToInt(sbbMin.X);
		Min.Y = RoundToInt(sbbMin.Y);
		Max.X = RoundToInt(sbbMax.X);
		Max.Y = RoundToInt(sbbMax.Y);
	}

	void CalcBaryCentricCoord(IntPoint target, float *outS, float *outT)
	{
		Vector2 w = (Vector3((float)(target.X) + 0.5f, (float)(target.Y) + 0.5f, 0.0f) - vt[0].position).ToVector2();
		float dotUW = u.Dot(w);
		float dotVW = v.Dot(w);
		*outS = (dotVV * dotUW - dotUV * dotVW) * invDenom;
		*outT = (dotUU * dotVW - dotUV * dotUW) * invDenom;
	}

	bool IsInTrianble(float s, float t)
	{
		if (s < 0.0f) return false;
		if (t < 0.0f) return false;
		if (s + t > 1.0f) return false;
		return true;
	}

	FragIn GetFragment(float s, float t)
	{
		FragIn result;
		result.uv = GetFragUV(s, t);
		result.color = GetFragVertexColor(s, t);
		return result;
	}


public:
	IntPoint Min;
	IntPoint Max;

private:
	Vector2 u;
	Vector2 v;
	float dotUU, dotUV, dotVV, invDenom;
	VertInOut vt[3];

	Vector2 GetFragUV(float s, float t)
	{
		return vt[0].uv * (1.0f - s - t) + vt[1].uv * s + vt[2].uv * t;
	}

	ULONG GetFragVertexColor(float s, float t)
	{
		BYTE RV0 = GetRValue(vt[0].color);
		BYTE RV1 = GetRValue(vt[1].color);
		BYTE RV2 = GetRValue(vt[2].color);

		BYTE GV0 = GetGValue(vt[0].color);
		BYTE GV1 = GetGValue(vt[1].color);
		BYTE GV2 = GetGValue(vt[2].color);

		BYTE BV0 = GetBValue(vt[0].color);
		BYTE BV1 = GetBValue(vt[1].color);
		BYTE BV2 = GetBValue(vt[2].color);

		BYTE FinalR = RoundToInt(RV0 * (1.0f - s - t) + RV1 * s + RV2 * t);
		BYTE FinalG = RoundToInt(GV0 * (1.0f - s - t) + GV1 * s + GV2 * t);
		BYTE FinalB = RoundToInt(BV0 * (1.0f - s - t) + BV1 * s + BV2 * t);
		return RGB32(FinalR, FinalG, FinalB);
	}

};

