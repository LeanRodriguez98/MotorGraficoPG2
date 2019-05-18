#pragma once
#include "Exports.h"
#include "TypeDefs.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/mesh.h>
#include "assimp/DefaultLogger.hpp"
#include "assimp/LogStream.hpp"
#include "TextureImporter.h"
#include <vector>
#include <iostream>
#include "Mesh.h"
#define GLM_ENABLE_EXPERIMENTAL
using namespace std;
using namespace glm;

class ENGINEDLL_API MeshLoader
{
public:                                                                                   
	MeshLoader();
	static MeshLoader * instance;
	static MeshLoader * GetInstance()
	{
		if (instance == NULL) 
			instance = new MeshLoader();
		return instance;
	}
	MeshLoader(MeshLoader const&) = delete;
	void operator = (MeshLoader const&) = delete;
	bool LoadMesh(const string& Filename,
		const string& texturePath, 
		vector<MeshEntry>& m_Entries, 
		vector<BMPData*>& m_Textures);
	void Clear(vector<BMPData*>& textures);
	bool InitFromScene(const aiScene* pScene, const string& Filename, vector<MeshEntry>& m_Entries, vector<BMPData*>& m_Textures);
	void InitMesh(unsigned int Index, const aiMesh* paiMesh, vector<MeshEntry>& m_Entries);
};

