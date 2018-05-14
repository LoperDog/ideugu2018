
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

void DrawCall (Mesh * MeshToDraw)
{
	V2F_CUSTOM* v2f = new V2F_CUSTOM [ MeshToDraw->VSize ];

	for ( int i = 0; i < MeshToDraw->VSize; i ++ )
	{
		Vertex v = MeshToDraw->Vertices [ i ];
		APPDATA_CUSTOM vdata;
		vdata.position = v.position;
		vdata.color = v.color;
		vdata.uv = v.uv;
		v2f[i] = VertexShader ( vdata );
	}

	for ( int i = 0; i < MeshToDraw->ISize; i+=3 )
	{
		Triangle t ( v2f [ MeshToDraw->Indices [ i ]],
			v2f [ MeshToDraw->Indices [ i+1 ]],
			v2f [ MeshToDraw->Indices [ i+2 ]] );

		// Rasterization
		for ( int y = t.Min.Y; y <= t.Max.Y; y++ )
		{
			for ( int x = t.Min.X; x <= t.Max.X; x++ )
			{
				Vector3 target ( ( float ) x + 0.5f, ( float ) y + 0.5f, 0.0f );
				float outS, outT;
				t.CalcBaryCentricCoord ( target, &outS, &outT );
				if ( t.IsInTrianble ( outS, outT ) )
				{
					V2F_CUSTOM v2f;
					v2f.position = t.GetFragmentPos ( target, outS, outT );
					v2f.color = t.GetFragmentColor ( target, outS, outT );
					v2f.uv = t.GetFragmentUV ( target, outS, outT );
					ULONG finalColor = FragmentShader ( v2f, outS, outT );
					g_CurrentColor = finalColor;
					PutPixel ( IntPoint(x, y) );
				}
			}
		}
	}

	if ( NULL != v2f )
	{
		delete [ ] v2f;
	}
}

static Mesh* m = new Mesh();

Matrix3 TMat, RMat, SMat, TRSMat;

V2F_CUSTOM VertexShader ( APPDATA_CUSTOM in )
{
  V2F_CUSTOM returndata;
  returndata.position = in.position * TRSMat;
  returndata.color = in.color;
  returndata.uv = in.uv;
	//return V2F_CUSTOM ( );
  return returndata;
}

ULONG FragmentShader (V2F_CUSTOM in, float s, float t )
{
	// Texture에서 색상 빼오기..
	if ( g_Texture->IsLoaded ( ) )
	{
		return g_Texture->TextureSample ( in.uv, s, t );
	}

	return in.color;
}

//void DrawLine(const Vector3& start, const Vector3& end)
//{
//	float length = (end - start).Dist();
//	float inc = 1.0f / length;
//
//	int maxLength = RoundToInt(length);
//	for (int i = 0; i <= maxLength; i++)
//	{
//		float t = inc * i;
//		if (t >= length) t = 1.0f;
//		Vector3 Pt = start * (1.0f - t) + end * t;
//		PutPixel(Pt.ToIntPoint());
//	}
//}

//void Draw2DTriangle(Triangle t)
//{
//	for (int y = t.Min.Y; y <= t.Max.Y; y++)
//	{
//		for (int x = t.Min.X; x <= t.Max.X; x++)
//		{
//			Vector3 target((float)x + 0.5f, (float)y + 0.5f, 0.0f);
//			float outS, outT;
//			t.CalcBaryCentricCoord(target, &outS, &outT);
//			if (t.IsInTrianble(outS, outT))
//			{
//				if (g_Texture->IsLoaded())
//				{
//					g_CurrentColor = g_Texture->GetTexturePixel(outS, outT, t);
//				}
//				else
//				{
//					g_CurrentColor = t.GetPixelColor(target, outS, outT);
//				}
//
//				PutPixel(IntPoint(x, y));
//			}			
//		}
//	}
//}

void InitFrame (void)
{

  Vector3 Pt1, Pt2, Pt3, Pt4;

  Pt1.SetPoint(-150, 150.0f);
  Pt2.SetPoint(150.0f, 150.0f);
  Pt3.SetPoint(150.0f, -150.0f);
  Pt4.SetPoint(-150.0f, -150.0f);



  static Vertex * v = new Vertex[4]();
  v[0].position = Pt1;
  v[0].color = RGB32(255, 0, 0);
  v[0].uv = Vector2(0.125f, 0.125f);

  v[1].position = Pt2;
  v[1].color = RGB32(0, 255, 0);
  v[1].uv = Vector2(0.25f, 0.125f);
  
  v[2].position = Pt3;
  v[2].color = RGB32(0, 0, 255);
  v[2].uv = Vector2(0.25f, 0.25f);

  v[3].position = Pt4;
  v[3].color = RGB32(255, 255, 255);
  v[3].uv = Vector2(0.125f, 0.25f);

  static int * index = new int[6];
  index[0] = 0;
  index[1] = 1;
  index[2] = 2;

  index[3] = 0;
  index[4] = 3;
  index[5] = 2;

  m->SetVertetices(v, 4);
  m->SetIndices(index, 6);
}

void UpdateFrame (void)
{
	// Buffer Clear
	SetColor(32, 128, 255);
	Clear();

	static float offsetX = 0.0f;
	static float angle = 0.0f;
	static float scale = 1.0f;

	if (GetAsyncKeyState(VK_LEFT)) offsetX -= 1.0f;
	if (GetAsyncKeyState(VK_RIGHT)) offsetX += 1.0f;
	if (GetAsyncKeyState(VK_UP)) angle += 1.0f;
	if (GetAsyncKeyState(VK_DOWN)) angle -= 1.0f;
	if (GetAsyncKeyState(VK_PRIOR)) scale *= 1.01f;
	if (GetAsyncKeyState(VK_NEXT)) scale *= 0.99f;


	TMat.SetTranslation(offsetX, 0.0f);
	RMat.SetRotation(angle);
	SMat.SetScale(scale);

	TRSMat = TMat * RMat * SMat;

	DrawCall ( m );
	// Buffer Swap 
	BufferSwap();
}
