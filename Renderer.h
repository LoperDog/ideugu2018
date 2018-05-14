#pragma once
#include "Mesh.h"
#include "Triangle.h"

void InitFrame(void);
void UpdateFrame(void);
bool IsInRange(int x, int y);
void PutPixel(IntPoint pt);
void DrawCall (Mesh* MeshToDraw);

V2F_CUSTOM VertexShader ( APPDATA_CUSTOM in );
ULONG FragmentShader ( V2F_CUSTOM in, float s, float t );