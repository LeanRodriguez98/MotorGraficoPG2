#pragma once
#include "Entity.h"
#include "Shape.h"

class ENGINEDLL_API  Mesh : public Shape
{
public:
	Mesh(Renderer * _renderer);
	~Mesh();
	void Draw();
	void DrawMesh(int drawType) override;
};

