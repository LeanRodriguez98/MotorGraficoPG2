#pragma once
#include "Exports.h"
#include "../external/glm-0.9.9.0/glm/glm.hpp"
#include "../external/glm-0.9.9.0/glm/gtc/matrix_transform.hpp"
using namespace glm;
class ENGINEDLL_API Material
{
	unsigned int ProgramID;
public:
	Material();
	~Material();
	unsigned int  LoadShaders(const char * vertex_file_path, const char * fragment_file_path);
	void Bind();
	void SetMatrixProperty(const char * name, mat4& modelViewProyectionMatrix);
};

