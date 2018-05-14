
#include "stdafx.h"
#include "Mesh.h"

Mesh::~Mesh ()
{
	if (NULL != Vertices)
	{
		delete[] Vertices;
		Vertices = NULL;
	}

	if (NULL != Indices)
	{
		delete[] Indices;
		Indices = NULL;
	}
}

void Mesh::SetVertetices (Vertex * NewVertices, size_t NewSize)
{
  Vertices = NewVertices;
  VSize = NewSize;
}

void Mesh::SetIndices (int * NewIndices, size_t NewSize)
{
  Indices = NewIndices;
  ISize = NewSize;
}
