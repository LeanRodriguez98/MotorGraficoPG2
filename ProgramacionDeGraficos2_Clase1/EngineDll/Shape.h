#pragma once
#include "Entity.h"
#include "Material.h"
class ENGINEDLL_API Shape: public Entity
{
public:

	float * vertex;
	unsigned int vertexBuffer;
	Material * material;
	void SetVertexBuffer(float * vertex, int cant);	
	Shape(Renderer * renderer);
	~Shape();
	virtual void Draw() = 0;
	void SetMaterial(Material * _material);
};

