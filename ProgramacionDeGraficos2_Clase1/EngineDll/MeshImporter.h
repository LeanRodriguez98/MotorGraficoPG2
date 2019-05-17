#pragma once
#include "Exports.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/mesh.h>
#include "assimp/DefaultLogger.hpp"
#include "assimp/LogStream.hpp"
#include "TextureImporter.h"
#include <vector>
#include <iostream>
using namespace std;
class ENGINEDLL_API MeshImporter
{
public:
	MeshImporter();
	~MeshImporter();
	static MeshImporter * instance;
	static MeshImporter* GetInstance()
	{
		if (instance == NULL) 
			instance = new MeshImporter();
		return instance;
	}
	void Clear(vector<BMPData*>& textures);
	float * GetMeshVertex(string path);
};

