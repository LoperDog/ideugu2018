
#include "stdafx.h"
#include "Vector.h"
#include "SoftRenderer.h"
#include "GDIHelper.h"
#include "Renderer.h"
#include "Triangle.h"
#include "Texture.h"

bool IsInRange(int x, int y)
{
	return (abs(x) < (g_nClientWidth / 2)) && (abs(y) < (g_nClientHeight / 2));
}

void PutPixel(IntPoint pt)
{
	if (!IsInRange(pt.X, pt.Y)) return;

	ULONG* dest = (ULONG*)g_pBits;

	int halfWidth = RoundToInt(g_nClientWidth * 0.5f);
	int halfHeight = RoundToInt(g_nClientHeight * 0.5f);

	DWORD offset = (halfHeight * g_nClientWidth - g_nClientWidth * pt.Y) + (halfWidth + pt.X);
	*(dest + offset) = g_CurrentColor;
}

void DrawLine(const Vector3& start, const Vector3& end)
{
	float length = (end - start).Dist();
	float inc = 1.0f / length;

	int maxLength = RoundToInt(length);
	for (int i = 0; i <= maxLength; i++)
	{
		float t = inc * i;
		if (t >= length) t = 1.0f;
		Vector3 Pt = start * (1.0f - t) + end * t;
		PutPixel(Pt.ToIntPoint());
	}
}

void Draw2DTriangle(Triangle t)
{
	for (int y = t.Min.Y; y <= t.Max.Y; y++)
	{
		for (int x = t.Min.X; x <= t.Max.X; x++)
		{
			Vector3 target((float)x + 0.5f, (float)y + 0.5f, 0.0f);
			float outS, outT;
			t.CalcBaryCentricCoord(target, &outS, &outT);
			if (t.IsInTrianble(outS, outT))
			{
				if (g_Texture->IsLoaded())
				{
					g_CurrentColor = g_Texture->GetTexturePixel(outS, outT, t);
				}
				else
				{
					g_CurrentColor = t.GetPixelColor(target, outS, outT);
				}

				PutPixel(IntPoint(x, y));
			}			
		}
	}
}

void Draw2DMesh(Mesh m) {
	Triangle t1(m.vertex[m.index[0]], m.vertex[m.index[1]], m.vertex[m.index[2]]);
	Triangle t2(m.vertex[m.index[3]], m.vertex[m.index[4]], m.vertex[m.index[5]]);

	Draw2DTriangle(t1);
	Draw2DTriangle(t2);
}

void UpdateFrame(void)
{
	// Buffer Clear
	SetColor(32, 128, 255);
	Clear();

	// Draw
	Vector3 Pt1, Pt2, Pt3, Pt4;

	static float offsetX = 0.0f;
	static float angle = 0.0f;
	static float scale = 1.0f;

	if (GetAsyncKeyState(VK_LEFT)) offsetX -= 1.0f;
	if (GetAsyncKeyState(VK_RIGHT)) offsetX += 1.0f;
	if (GetAsyncKeyState(VK_UP)) angle += 1.0f;
	if (GetAsyncKeyState(VK_DOWN)) angle -= 1.0f;
	if (GetAsyncKeyState(VK_PRIOR)) scale *= 1.01f;
	if (GetAsyncKeyState(VK_NEXT)) scale *= 0.99f;

	Matrix3 TMat, RMat, SMat;
	TMat.SetTranslation(offsetX, 0.0f);
	RMat.SetRotation(angle);
	SMat.SetScale(scale);
	Matrix3 TRSMat = TMat * RMat * SMat;

	Pt1.SetPoint(-150, 150.0f);
	Pt2.SetPoint(150.0f, 150.0f);
	Pt3.SetPoint(150.0f, -150.0f);
	Pt4.SetPoint(-150.0f, -150.0f);

	Vertex v1(Pt1 * TRSMat);
	v1.color = RGB32(255, 0, 0);
	//v1.uv = Vector2(0.0f, 0.0f);
	v1.uv = Vector2(0.125f, 0.125f);
	Vertex v2(Pt2 * TRSMat);
	v2.color = RGB32(0, 255, 0);
	//v2.uv = Vector2(1.0f, 0.0f);
	v2.uv = Vector2(0.25f, 0.125f);
	Vertex v3(Pt3 * TRSMat);
	v3.color = RGB32(0, 0, 255);
	//v3.uv = Vector2(1.0f, 1.0f);
	v3.uv = Vector2(0.25f, 0.25f);
	Triangle T1(v1, v2, v3);

	Vertex v4(Pt4 * TRSMat);
	v4.color = RGB32(255, 255, 0);
	//v4.uv = Vector2(0.0f, 1.0f);
	v4.uv = Vector2(0.125f, 0.25f);
	Triangle T2(v1, v4, v3);

	Mesh m(v1, v2, v4, v3);

	//Draw2DTriangle(T1);
	//Draw2DTriangle(T2);
	Draw2DMesh(m);

	// Buffer Swap 
	BufferSwap();
}
