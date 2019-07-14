#pragma once

#include "Exports.h"
#include "Renderer.h"
#include "Material.h"
#include <vector>

struct MeshEntry
{
	vector<float> * vertexArray;
	vector<float> * uvArray;
	vector<unsigned int> * indexArray;
};

struct MeshData
{
	unsigned int vertexBufferID;
	unsigned int uvBufferID;
	unsigned int indexBufferID;
	unsigned int textureBufferID;
	unsigned int programID;
	unsigned int vertexCount;
	unsigned int UVCount;
	unsigned int indexCount;
	unsigned int * index;
	float * vertex;
	float * UVVertex;
	Material * material;
};

