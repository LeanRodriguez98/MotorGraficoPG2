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
#include "Camera.h"
using namespace std;
using namespace Assimp;

class Renderer;
class Mesh;
class Node;

class ENGINEDLL_API MeshLoader
{

private:
	MeshLoader();
	static MeshLoader *instance;
	const aiScene* scene = NULL;
	Importer importer;
	void InitMesh(const aiMesh* _paiMesh, Mesh* _mesh);
    void ProcessNodes(const char * _texturePath, Node * _rootNode, aiNode * _node, const aiScene * _aiScene, Renderer * _renderer, Camera * _camera);
	void GenerateBoundingBox(Node * _rootNode);
	vec3 boundingBoxMin;
	vec3 boundingBoxMax;
public:
	void LoadMesh(const char * _modelPath, const char * _texturePath, Node * _rootNode, Renderer* _renderer, Camera * _camera);
	static MeshLoader* GetInstance()
	{
		if (instance == NULL)
		{
			instance = new MeshLoader();
		}
		return instance;
	}
};

