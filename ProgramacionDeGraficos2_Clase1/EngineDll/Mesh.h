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

	bool isBsp = false;
	vec3 bspForward;
public:
	BoundingBox3D * boundingBox3D;
	Mesh(Renderer * _renderer,  const char * _textureFile, Camera * _camera);
	~Mesh();
	MeshEntry * GetMeshEntry();
	void SetBSP( Node * _node);
	bool GetIsBsp();
	vec3 GetForwardBSP();
	void SetMeshEntry(MeshEntry * _meshEntry);
	void Draw() override;
};