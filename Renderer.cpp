
#include "stdafx.h"
#include "SoftRenderer.h"
#include "GDIHelper.h"
#include "Renderer.h"
#include "Vector.h"

bool IsInRange(int x, int y);
void PutPixel(int x, int y);
void DrawCircle(Vector2, int r);
void DrawRectangle(Vector2 leftTop, Vector2 rightBottom);
Vector2 SetScale(Vector2 dotPos, int hor, int ver);
void DrawLine(Vector3 start, Vector3 dest);


bool IsInRange(int x, int y)
{
	return (abs(x) < (g_nClientWidth / 2)) && (abs(y) < (g_nClientHeight / 2));
}

void PutPixel(int x, int y)
{
	if (!IsInRange(x, y)) return;

	ULONG* dest = (ULONG*)g_pBits;
	DWORD offset = g_nClientWidth * g_nClientHeight / 2 + g_nClientWidth / 2 + x + g_nClientWidth * -y;
	*(dest + offset) = g_CurrentColor;
}

static Vector3 Point_1, Point_2;
static Vector2 Point_3, Point_4;


float FLeft = -10.0f;
float FTop = -2.0f;
float FRight = 10.0f;
float FBottom = 2.0f;

void UpdateFrame(void)
{

	static float trX = 0.0f;
	static float trY = 0.0f;
	static float rotation = 0.0f;
	static float scale = 0.0f;


	bool IsMove = false;

	// Buffer Clear
	SetColor(102, 102, 102);
	Clear();

	// Draw
	SetColor(255, 0, 0);

	Matrix2 m_temp_1;
	Matrix3 m_temp_2;

	m_temp_1.SetIdentity();
	m_temp_2.SetIdentity();

	Point_3.X = FLeft;
	Point_3.Y = FTop;
	Point_4.X = FRight;
	Point_4.Y = FBottom;

	if (GetAsyncKeyState(VK_UP)) {
		rotation += 0.01f;
		m_temp_1.SetRotation(rotation);
		Point_3 = Point_3 * m_temp_1;
		Point_4 = Point_4 * m_temp_1;
		IsMove = true;
	}
	if (GetAsyncKeyState(VK_RIGHT)) {
		scale += 0.01f;
		m_temp_1.SetScale(scale);
		Point_3 = Point_3 * m_temp_1;
		IsMove = true;
	}
	if (GetAsyncKeyState(VK_LEFT)) {
		scale -= 0.01f;
		m_temp_1.SetScale(scale);
		Point_3 = Point_3 * m_temp_1;
		IsMove = true;
	}
	

	Point_1.SetPoint(Point_3.X, Point_3.Y);
	Point_2.SetPoint(Point_4.X, Point_4.Y);


	if (GetAsyncKeyState(VK_DOWN)) {
		trX += 0.001f;
		trY += 0.001f;
		m_temp_2.SetTranform(trX, trY);

		Point_1 = (Point_1 * m_temp_2);
		Point_2 = Point_1 + Point_2;
		IsMove = true;
	}

	// 현재상태 저장
	FLeft = Point_1.X;
	FTop = Point_1.Y;
	FRight = Point_2.X;
	FTop = Point_2.Y;

	SetColor(0, 0, 0);
	//if(IsMove)
	DrawLine(Point_1, Point_2);
	


	// Buffer Swap 
		BufferSwap();
}

void DrawLine(Vector3 start, Vector3 dest)
{
	PutPixel(start.X, start.Y);
	PutPixel(dest.X, dest.Y);

	float countX = start.X - dest.X;
	if (countX < 0) countX *= -1;
	float countY = start.Y - dest.Y;
	if (countY < 0) countY *= -1;

	float dotVal = 100 / (countX * countY);
	//float t = 0.5;

	int loopVal = 0;

	for (float t = 0.0f; t < 1; t += dotVal)
	{
		Vector3 tempStart = start;
		Vector3 tempDest = dest;

		float frontP = 1 - t;
		float frontD = t;

		tempStart.X *= frontP;
		tempStart.Y *= frontP;

		tempDest.X *= frontD;
		tempDest.Y *= frontD;

		Vector3 between;
		between.SetPoint(tempStart.X + tempDest.X, tempStart.Y + tempDest.Y);

		SetColor(0, 0, 0);
		PutPixel(between.X, between.Y);
		loopVal++;
	}

}


Vector2 SetScale(Vector2 dotPos, float scaleVal) {

	Matrix2 tempMat(scaleVal, 0, scaleVal, 0);

	return dotPos * tempMat;
}


void DrawCircle(Vector2 drawPos, int r) {

	for (int i = -r ; i < r; i++)
	{
		for (int j = -r; j < r; j++)
		{
			if ((i * i) + (j * j) < (r * r)) {
				PutPixel(i , j );

			}
		}
	}
}

void DrawRectangle(Vector2 leftTop, Vector2 rightBottom) {


	Matrix2 rot;

	static float angle = 0.0f;
	angle += 0.001f;

	rot.SetRotation(angle);
	Vector2 recTemp(5, 5);
	Vector2 NewTemp = recTemp * rot;
	PutPixel(NewTemp.X, NewTemp.Y);

	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			if (i == j)
			{
				Vector2 recTemp(i, j);
				recTemp = recTemp * rot;
				PutPixel(recTemp.X, recTemp.Y);
			}
		}
	}

	for (int i = (int)leftTop.Y; i > (int)rightBottom.Y; i--)
	{
		for (int j = (int)leftTop.X; j < (int)rightBottom.X; j++)
		{
			Vector2 recTemp(i, j);
			recTemp = recTemp * rot;
			PutPixel(recTemp.X, recTemp.Y);
		}
	}
}
