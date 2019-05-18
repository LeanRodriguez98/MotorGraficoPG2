#pragma once
#include "Exports.h"
#include "Entity.h"
#include "Shape.h"
#include "MeshImporter.h"
#include "MeshLoader.h"
class ENGINEDLL_API  Mesh : public Shape
{
public:
	Mesh(Renderer * _renderer, Material* material, Layers layer, string modelPath, string texturePath);
	~Mesh();
	void Draw();
	void DrawMesh(int drawType) override;
	Renderer * renderer;

	vector<MeshEntry> m_Entries;
	vector<BMPData*> m_Textures;
	vector<unsigned int> bufferTextures;

	char* texturePath;

};

