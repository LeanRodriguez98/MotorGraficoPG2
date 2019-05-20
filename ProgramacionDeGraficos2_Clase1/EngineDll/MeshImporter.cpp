#include "MeshImporter.h"

MeshEntry::MeshEntry()
{
	vertexBuffer = NULL;
	indexBuffer = NULL;
	cantIndex = 0;
};

MeshEntry::~MeshEntry()
{
	if (vertexBuffer != NULL) 
		glDeleteBuffers(1, &vertexBuffer);
	if (indexBuffer != NULL) 
		glDeleteBuffers(1, &indexBuffer);
}

void MeshEntry::Init(const vector<Vertex>& _vertex, const vector<unsigned int>& _index, Renderer* _renderer)
{
	cantIndex = _index.size();

	float* meshPositions = new float[_vertex.size() * 3];
	float* meshTextures = new float[_vertex.size() * 2];
	float* meshNormals = new float[_vertex.size() * 3];

	for (int i = 0; i < _vertex.size(); i++)
	{
		meshPositions[i * 3] = _vertex[i].vertexPosition.x;
		meshPositions[i * 3 + 1] = _vertex[i].vertexPosition.y;
		meshPositions[i * 3 + 2] = _vertex[i].vertexPosition.z;
		meshTextures[i * 2] = _vertex[i].vertexTexture.x;
		meshTextures[i * 2 + 1] = _vertex[i].vertexTexture.y;
		meshNormals[i * 3] = _vertex[i].vertexNormal.x;
		meshNormals[i * 3 + 1] = _vertex[i].vertexNormal.y;
		meshNormals[i * 3 + 2] = _vertex[i].vertexNormal.z;
	}

	vertexBuffer = _renderer->GenerateBuffer(meshPositions, sizeof(float) * _vertex.size() * 3);
	indexBuffer = _renderer->GenerateIndexBuffer(_index);
	uvBuffer = _renderer->GenerateBuffer(meshTextures, sizeof(float) * _vertex.size() * 2);
}
