#pragma once

#include "stdafx.h"
#include "Vertex.h"

struct Mesh
{
	Mesh() : Vertices(NULL), Indices(NULL), VSize(0), ISize(0) {} ;
	//~Mesh();
	//void SetVertices(Vertex* NewVertices, size_t NewSize);
	//void SetIndices(int* NewIndices, size_t NewSize);
	bool IsInitialized() { return ((NULL != Vertices) && (NULL != Indices) && (ISize % 3 == 0)); }

	Vertex* Vertices;
	size_t VSize;

	int* Indices;
	size_t ISize;
};