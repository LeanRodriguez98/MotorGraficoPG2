#pragma once
#include "Entity.h"
#include "Material.h"

#define PRIMITIVE_TRIANGLE 0x0004
#define PRIMITIVE_TRIANGLE_STRIP 0x0005
#define PRIMITIVE_TRIANGLE_FAN 0x0006

class  ENGINEDLL_API Shape :public Entity
{
protected:
	Material * material;

	unsigned int vertexBufferID;
	unsigned int colorBufferID;
	float * vertex;
	float * colorVertex;
	int vertexCount;
	int colorVertexCount;


public:
	Shape(Renderer *render);
	~Shape();
	void SetVertexBuffer(float* _vertex, int _cant);
	void SetColorBuffer(float* _vertex, int _cant);
	virtual void Draw() = 0;
	virtual void  DrawMesh(int drawType);
	void SetMaterial(Material* material);


};



