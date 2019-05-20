#pragma once

#include "Exports.h"
#include "Renderer.h"
#include "../external/glew-2.1.0/include/GL/glew.h"
#include "../external/glm-0.9.9.0/glm/vec2.hpp"
#include "../external/glm-0.9.9.0/glm/vec3.hpp"
#include <vector>

using namespace std;
using namespace glm;

struct Vertex
{
	vec3 vertexPosition;
	vec2 vertexTexture;
	vec3 vertexNormal;

	Vertex() {}

	Vertex(const vec3& _vertexPosition, const vec2& _vertexTexture, const vec3& _vertexNormal)
	{
		vertexPosition = _vertexPosition;
		vertexTexture = _vertexTexture;
		vertexNormal = _vertexNormal;
	}
};

struct MeshEntry
{
	void Init(const vector<Vertex>& _vertex, const vector<unsigned int>& _index, Renderer* _renderer);

	unsigned int vertexBuffer;
	unsigned int indexBuffer;
	unsigned int uvBuffer;
	unsigned int cantIndex;

	MeshEntry();
	~MeshEntry();
};



