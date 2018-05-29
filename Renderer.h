#pragma once

#include "Mesh.h"

void InitFrame(void);
void UpdateFrame(void);
void DrawCall(Mesh* MeshToDraw);
bool IsInRange(int x, int y);
void PutPixel(IntPoint pt);

