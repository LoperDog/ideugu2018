#pragma once

#include "stdafx.h"
#include "Vector.h"

class Texture
{
public:
	Texture() : Buffer(NULL), width(0), height(0) {}
	~Texture() { if (Buffer != NULL) delete Buffer; }

	bool IsLoaded() { return (Buffer != NULL);  }

	bool LoadBMP(char* filename);
	ULONG GetPixel(int x, int y);
	//ULONG GetTexturePixel(float s, float t, const Triangle& tri);
	ULONG TextureSample ( Vector2 TexCoord, float s, float t );

	int width;
	int height;		
	ULONG* Buffer;
};