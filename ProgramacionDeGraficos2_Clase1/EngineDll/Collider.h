#pragma once
#include "Exports.h"
#include "Definitions.h"
#include <iostream>
#include "../external/glm-0.9.9.0/glm/glm.hpp"
#include "../external/glm-0.9.9.0/glm/gtc/matrix_transform.hpp"
using namespace glm;

class ENGINEDLL_API Collider
{
private:
	float height;
	float width;
	vec2 pivotPosition;
	Layers layer;
	bool isStatic;
public:
	Collider(vec2 _pivotPosition, float _height, float _width, Layers _layer, bool isStatic);
	unsigned int GetXPosition();
	unsigned int GetYPosition();
	vec2 GetPivot();
	unsigned int GetHeight();
	unsigned int GetWidth();
	Layers GetLayer();
	bool GetIsStatic();
	~Collider();
};



