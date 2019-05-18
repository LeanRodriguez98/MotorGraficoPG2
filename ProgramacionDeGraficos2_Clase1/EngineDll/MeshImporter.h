#pragma once
#include "Exports.h"
#include "TypeDefs.h"

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <vector>
#include "Mesh.h"
#include "Definitions.h"

#define GLM_ENABLE_EXPERIMENTAL
struct ENGINEDLL_API Vertex
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


	void Init(const vector<Vertex>& Vertices,
		const vector<unsigned int>& Indices);


	unsigned int verticesBuffer;
	unsigned int indicesBuffer;
	unsigned int uvBuffer;

	unsigned int NumIndices;
	unsigned int MaterialIndex;
	MeshEntry();

	~MeshEntry();
};

class MeshImporter
{
public:
	MeshImporter();
	~MeshImporter();

};

