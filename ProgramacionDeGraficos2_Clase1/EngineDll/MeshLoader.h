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
#include "Node.h"
using namespace std;
using namespace Assimp;

class Mesh;

class ENGINEDLL_API MeshLoader
{
private:
	MeshLoader();
	static MeshLoader *instance;
	const aiScene* scene = NULL;
	Importer importer;
	void InitMesh(const aiMesh* paiMesh, Mesh* mesh);
    void ProcessNodes(const char * fbxFile, const char * textFile, Node * rootNode, aiNode * node, const aiScene * scene, Renderer * render);
public:
	void LoadMesh(const char * _modelPath, const char * _texturePath, Node * _rootNode, Renderer* _renderer);
	static MeshLoader* GetInstance()
	{
		if (instance == NULL)
		{
			instance = new MeshLoader();
		}
		return instance;
	}
};

