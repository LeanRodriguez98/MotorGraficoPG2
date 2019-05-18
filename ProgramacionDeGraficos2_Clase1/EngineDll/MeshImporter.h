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
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <gl/glew.h>
using namespace std;
using namespace glm;

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
	bool LoadMesh(const string& Filename);
	void Clear(vector<BMPData*>& textures);
	bool InitFromScene(const aiScene* pScene, const std::string& Filename);
	void InitMesh(unsigned int Index, const aiMesh* paiMesh);

	struct Vertex
	{
		vec3 m_pos;
		vec2 m_tex;
		vec3 m_normal;

		Vertex() {}

		Vertex(const vec3& pos, const vec2& tex, const vec3& normal)
		{
			m_pos = pos;
			m_tex = tex;
			m_normal = normal;
		}
	};

	struct MeshEntry {
		MeshEntry();

		~MeshEntry();

		void Init(const vector<Vertex>& Vertices,
			const vector<unsigned int>& Indices);
			
		GLuint VB;
		GLuint IB;
		unsigned int NumIndices;
	};

	vector<MeshEntry> m_Entries;
	vector<BMPData*> m_Textures;
};

