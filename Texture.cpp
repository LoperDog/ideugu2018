
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

ULONG Texture::GetTexturePixel(Vector2 uv)
{
	int PixelX = (int)floorf(uv.X * width);
	int PixelY = (int)floorf(uv.Y * height);

	PixelX = PixelX % width;
	PixelY = PixelY % height;
	return GetPixel(PixelX, PixelY);
}
