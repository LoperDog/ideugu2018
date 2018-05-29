
#include "stdafx.h"
#include "Mesh.h"

//Mesh::~Mesh()
//{
//	if (NULL != Indices)
//	{
//		delete[] Indices;
//		Indices = NULL;
//		ISize = 0;
//	}
//
//	if (NULL != Vertices)
//	{
//		delete[] Vertices;
//		Vertices = NULL;
//		VSize = 0;
//	}
//}

//void Mesh::SetVertices(Vertex* NewVertices, size_t NewSize)
//{
//	if (NULL == NewVertices) return;
//
//	if (NULL != Vertices)
//	{
//		delete[] Vertices;
//		Vertices = NULL;
//		VSize = 0;
//	}
//
//	Vertices = NewVertices;
//	VSize = NewSize;
//}
//
//void Mesh::SetIndices(int * NewIndices, size_t NewSize)
//{
//	if (NULL == NewIndices) return;
//
//	if (NULL != Indices)
//	{
//		delete[] Indices;
//		Indices = NULL;
//		ISize = 0;
//	}
//
//	Indices = NewIndices;
//	ISize = NewSize;
//}
