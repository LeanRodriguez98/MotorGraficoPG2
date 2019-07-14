#pragma once

#include "Shape.h"
#include "Definitions.h"
#include "MeshLoader.h"
#include "TextureImporter.h"
#include "Component.h"
#include "Node.h"

class ENGINEDLL_API Mesh : public Component
{
private:

	unsigned int textureID;
	const char * textureFile;
	MeshData * meshData;
	MeshEntry * meshEntry;
	BMPData BMPTexture;

public:
	Mesh(Renderer * _renderer, const char* _meshFile, const char * _textureFile, Node * _rootNode);
	~Mesh();
	MeshEntry * GetMeshEntry();
	void SetMeshEntry(MeshEntry * _meshEntry);
	void Draw() override;
};