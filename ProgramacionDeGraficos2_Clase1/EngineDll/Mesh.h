#pragma once

#include "Shape.h"
#include "Definitions.h"
#include "MeshLoader.h"
#include "TextureImporter.h"

class ENGINEDLL_API Mesh : public Shape
{
private:
	char* texturePath;
	vector<MeshEntry> meshEntries;
	vector<BMPData> meshTextures;
	vector<unsigned int> bufferTextureID;

public:
	void Draw() override;
	void Update();
	Mesh(string _modelPath, string _texturePath, Renderer* _renderer);
	~Mesh();
};
