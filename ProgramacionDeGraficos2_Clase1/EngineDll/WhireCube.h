#pragma once
#include "Shape.h"
#include "Renderer.h"
#include "Exports.h"
class ENGINEDLL_API WhireCube : public Shape
{
public:
	WhireCube(Renderer * _renderer);
	~WhireCube();
	void Draw();
};

