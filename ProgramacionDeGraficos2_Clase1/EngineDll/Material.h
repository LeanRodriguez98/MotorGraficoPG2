#pragma once
#include "Exports.h"
#include "../external/glm-0.9.9.0/glm/glm.hpp"
#include "../external/glm-0.9.9.0/glm/gtc/matrix_transform.hpp"
class ENGINEDLL_API Material
{
	unsigned int ProgramID;
	unsigned int textureId;
public:
	Material();
	~Material();
	void Bind();
	unsigned int  LoadShaders(const char * vertex_file_path, const char * fragment_file_path);
	void SetMatrixProperty(const char* name, glm::mat4& mat);
	void BindTexture(const char* name, unsigned int textureBufferId);
};


