#pragma once

#include "Shape.h"
#include "Definitions.h"
#include "MeshLoader.h"
#include "TextureImporter.h"
#include "Component.h"
#include "Node.h"
#include "BoundingBox3D.h"
#include "Camera.h"
class ENGINEDLL_API Mesh : public Component
{
private:

	unsigned int textureID;
	const char * textureFile;
	MeshData * meshData;
	MeshEntry * meshEntry;
	BMPData BMPTexture;
	Camera * camera;
public:
	BoundingBox3D * boundingBox3D;
	Mesh(Renderer * _renderer,  const char * _textureFile, Camera * _camera);
	~Mesh();
	MeshEntry * GetMeshEntry();
	void SetMeshEntry(MeshEntry * _meshEntry);
	void Draw() override;
};