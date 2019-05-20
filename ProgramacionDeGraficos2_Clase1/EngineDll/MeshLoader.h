#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "TextureImporter.h"
#include "Exports.h"
#include "MeshImporter.h"
#include "../external/assimp/include/assimp/Importer.hpp"
#include "../external/assimp/include/assimp/postprocess.h"
#include "../external/assimp/include/assimp/scene.h"
#include "../external/glew-2.1.0/include/GL/glew.h"
#include "../external/glfw-3.2.1/include/GLFW/glfw3.h"
#include "../external/glm-0.9.9.0/glm/glm.hpp"
#include "../external/glm-0.9.9.0/glm/glm.hpp"

using namespace std;
using namespace Assimp;
class ENGINEDLL_API MeshLoader
{
private:
	MeshLoader();
	static MeshLoader *instance;
	const aiScene* scene = NULL;
	Importer importer;
	void InitFromScene(const aiScene* _pScene, const string& _texturePath, vector<MeshEntry>& _meshEntries, vector<BMPData>& _meshTextures, Renderer* _renderer);
	void InitMesh(unsigned int _index, const aiMesh* _paiMesh, vector<MeshEntry>& _meshEntries, Renderer* _renderer);

public:
	void LoadMesh(const string& _modelPath, const string& _texturePath, vector<MeshEntry>& _meshEntries, vector<BMPData>& _meshTextures, Renderer* _renderer);
	static MeshLoader* GetInstance()
	{
		if (instance == NULL)
		{
			instance = new MeshLoader();
		}
		return instance;
	}
};

