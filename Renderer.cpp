
#include "stdafx.h"
#include "Vector.h"
#include "SoftRenderer.h"
#include "GDIHelper.h"
#include "Renderer.h"
#include "Triangle.h"
#include "Texture.h"
#include "Transform.h"

Mesh g_Quad;
Matrix3 g_ShaderMatrix;
bool g_Init = false;

VertInOut VertexShader(VertInOut v);
ULONG FragmentShader(FragIn f);

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

void InitFrame(void)
{
	Vertex Vertices[4] = { 
		{ { -30.0f, -30.0f, 1.0f }, RGB32(255, 0, 0) ,{ 0.125f, 0.25f } },
		{ { -30.0f, 30.0f, 1.0f }, RGB32(0, 255, 0) ,{ 0.125f, 0.125f } },
		{ { 30.0f, 30.0f, 1.0f }, RGB32(0, 0, 255) ,{ 0.25f, 0.125f } },
		{ { 30.0f, -30.0f, 1.0f }, RGB32(255, 0, 255) ,{ 0.25f, 0.25f } }
	};

	int Indices[6] = { 0, 1, 2, 0, 2, 3 };
	g_Quad.VSize = 4;
	g_Quad.ISize = 6;
	g_Quad.Vertices = new Vertex[g_Quad.VSize];
	memcpy(g_Quad.Vertices, Vertices, sizeof(Vertex) * g_Quad.VSize);
	g_Quad.Indices = new int[g_Quad.ISize];
	memcpy(g_Quad.Indices, Indices, sizeof(int) * g_Quad.ISize);
	
	g_Init = true;	
}

void UpdateFrame(void)
{
	// First Frame Init
	if(!g_Init) InitFrame();

	// Buffer Clear
	SetColor(32, 128, 255);
	Clear();

	// Set Matrix
	static float offsetX = 0.0f;
	static float angle = 0.0f;
	static float scale = 1.0f;
	static Vector2 camLocation(0.0f, 0.0f);
	static float camRotation = 0.0f;

	if (GetAsyncKeyState(VK_LSHIFT))
	{
		if (GetAsyncKeyState(VK_LEFT)) camLocation.X -= 1.0f;
		if (GetAsyncKeyState(VK_RIGHT)) camLocation.X += 1.0f;
		if (GetAsyncKeyState(VK_UP)) camLocation.Y += 1.0f;
		if (GetAsyncKeyState(VK_DOWN)) camLocation.Y -= 1.0f;
		if (GetAsyncKeyState(VK_PRIOR)) camRotation += 1.0f;
		if (GetAsyncKeyState(VK_NEXT)) camRotation -= 1.0f;
	}
	else
	{
		if (GetAsyncKeyState(VK_LEFT)) offsetX -= 1.0f;
		if (GetAsyncKeyState(VK_RIGHT)) offsetX += 1.0f;
		if (GetAsyncKeyState(VK_UP)) angle += 1.0f;
		if (GetAsyncKeyState(VK_DOWN)) angle -= 1.0f;
		if (GetAsyncKeyState(VK_PRIOR)) scale *= 1.01f;
		if (GetAsyncKeyState(VK_NEXT)) scale *= 0.99f;
	}

	Transform2D QuadTransform(Vector2(offsetX, 0.0f), angle, scale);
	Matrix3 ModelMat = QuadTransform.GetTRSMatrix();

	Transform2D CameraTransform(camLocation, camRotation, 1.0f);
	Matrix3 ViewMat = CameraTransform.GetViewMatrix();

	g_ShaderMatrix = ViewMat * ModelMat;

	// Axis Draw
	Vector3 XStart((float)g_nClientWidth * -2.5f + camLocation.X, 0.0f, 1.0f);
	Vector3 XEnd((float)g_nClientWidth * 2.5f + camLocation.X, 0.0f, 1.0f);
	SetColor(255, 0, 0);
	DrawLine(XStart * ViewMat , XEnd * ViewMat);

	Vector3 YStart(0.0f, (float)g_nClientHeight * -2.5f + camLocation.Y, 1.0f);
	Vector3 YEnd(0.0f, (float)g_nClientHeight * 2.5f + camLocation.Y, 1.0f);
	SetColor(0, 255, 0);
	DrawLine(YStart * ViewMat, YEnd * ViewMat);

	// Draw
	DrawCall(&g_Quad);

	// Buffer Swap 
	BufferSwap();
}

void DrawCall(Mesh * MeshToDraw)
{
	if (MeshToDraw->IsInitialized())
	{
		VertInOut* vOut = new VertInOut[MeshToDraw->VSize];
		// Vertex Shader
		for (int i = 0; i < MeshToDraw->VSize; i++)
		{
			Vertex vt = MeshToDraw->Vertices[i];
			VertInOut vIn(vt.position, vt.uv, vt.color);
			vOut[i] = VertexShader(vIn);
		}

		// Rasterization
		for (int i = 0; i < MeshToDraw->ISize; i += 3)
		{
			int index1 = MeshToDraw->Indices[i];
			int index2 = MeshToDraw->Indices[i + 1];
			int index3 = MeshToDraw->Indices[i + 2];

			Triangle t(vOut[index1], vOut[index2], vOut[index3]);
			for (int y = t.Min.Y; y <= t.Max.Y; y++)
			{
				for (int x = t.Min.X; x <= t.Max.X; x++)
				{
					IntPoint target(x, y);
					float outS, outT;
					t.CalcBaryCentricCoord(target, &outS, &outT);
					if (t.IsInTrianble(outS, outT))
					{
						// Fragment Shader
						FragIn frag = t.GetFragment(outS, outT);
						g_CurrentColor = FragmentShader(frag);
						PutPixel(target);
					}
				}
			}
		}
	}
}

VertInOut VertexShader(VertInOut v)
{
	VertInOut result;
	result.color = v.color;
	result.uv = v.uv;
	result.position = v.position * g_ShaderMatrix;
	return result;
}

ULONG FragmentShader(FragIn f)
{
	ULONG finalColor;
	if (g_Texture->IsLoaded())
	{
		finalColor = g_Texture->GetTexturePixel(f.uv);
	}
	else
	{
		finalColor = f.color;
	}

	return finalColor;
}
