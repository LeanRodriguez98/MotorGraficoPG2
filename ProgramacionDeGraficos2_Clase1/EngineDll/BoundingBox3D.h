#pragma once

#include "Exports.h"
#include "Renderer.h"
#include "Definitions.h"
#include <iostream>
#include "../external/glm-0.9.9.0/glm/glm.hpp"
#include "../external/glm-0.9.9.0/glm/gtc/matrix_transform.hpp"
using namespace std;
using namespace glm;
#define CANT_VERTEX 8
class ENGINEDLL_API BoundingBox3D
{
private:
	vec3 boundingBox3D[CANT_VERTEX];
	Renderer * renderer;
public:
	vec3 GetVertex(int _index);
	void SetVertex(glm::vec3 _boundingBox3D[CANT_VERTEX]);
	BoundingBox3D(Renderer * _renderer);
};

