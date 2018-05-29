#pragma once

#include "stdafx.h"
#include "Vector.h"

struct Vertex
{
public:
	Vertex() {}
	Vertex(Vector3 v) : position(v) { }
	Vertex(Vector3 v, ULONG c, Vector2 u) : position(v), color(c), uv(u) { }
	Vector3 position;
	ULONG color;
	Vector2 uv;
};
