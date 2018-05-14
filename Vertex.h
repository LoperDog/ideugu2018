#pragma once
#include "stdafx.h"
#include "Vector.h"

struct Vertex
{
public:
	Vertex () {}
	Vertex (Vector3 v) { position = v; }
	Vector3 position;
	ULONG color;
	Vector2 uv;
};
