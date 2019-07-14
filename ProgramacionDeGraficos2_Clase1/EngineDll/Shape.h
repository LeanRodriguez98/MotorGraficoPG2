#pragma once
#include "Entity.h"
#include "Material.h"
#include "TextureImporter.h"

#define PRIMITIVE_TRIANGLE 0x0004
#define PRIMITIVE_TRIANGLE_STRIP 0x0005
#define PRIMITIVE_TRIANGLE_FAN 0x0006
#define PRIMITIVE_QUAD 0x0007

class  ENGINEDLL_API Shape :public Entity
{
protected:


	unsigned int vertexBufferID;
	unsigned int colorBufferID;
	unsigned int textureBufferId;
	unsigned int UVBufferId;
	unsigned int indexBufferID;

	unsigned int * indexBuffer;
	float * vertex;
	float * colorVertex;
	float * textureUVvertex;
	bool dispouse;
	bool dispuseColor;
	int vertexCount;
	int colorVertexCount;
	//int indexVertexCount;

public:
	Shape(Renderer *render);
	~Shape();
	void SetVertexBuffer(float* _vertex, int _cant);
	void SetColorBuffer(float* _vertex, int _cant);
	void SetIndexBuffer(unsigned int* vertices, int count);
	virtual void Draw() = 0;
	virtual void  DrawMesh(int drawType);
	void SetMaterial(Material* material);


};



