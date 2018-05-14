
#include "stdafx.h"
#include "Texture.h"
#include "Bmp.h"

bool Texture::LoadBMP(char * filename)
{
	if (Buffer)
	{
		delete Buffer;
		Buffer = NULL;
	}

	Buffer = OpenBMP(filename, &width, &height);
	return (Buffer != NULL);
}

ULONG Texture::GetPixel(int x, int y)
{
	if (x >= width || y >= height)
	{
		::MessageBox(NULL, L"Invalide X, Y size", L"Texture Error", MB_OK);
	}

	return ::GetPixel(x, width, y, Buffer);
}

//ULONG Texture::GetTexturePixel(float s, float t, const Triangle & tri)
//{
//	Vector2 UV0 = tri.vt[0].uv;
//	Vector2 UV0ToUV1 = tri.vt[1].uv - tri.vt[0].uv;
//	Vector2 UV0ToUV2 = tri.vt[2].uv - tri.vt[0].uv;
//
//	Vector2 UVResult = UV0 + UV0ToUV1 * s + UV0ToUV2 * t;
//	int PixelX = (int)floorf(UVResult.X * width);
//	int PixelY = (int)floorf(UVResult.Y * height);
//
//	PixelX = PixelX % width;
//	PixelY = PixelY % height;
//	return GetPixel(PixelX, PixelY);
//}

ULONG Texture::TextureSample ( Vector2 TexCoord, float s, float t )
{
	int PixelX = ( int ) floorf ( TexCoord.X * width );
	int PixelY = ( int ) floorf ( TexCoord.Y * height );

	PixelX = PixelX % width;
	PixelY = PixelY % height;
	return GetPixel ( PixelX, PixelY );
}
