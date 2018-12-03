#include "Triangle.h"
Triangle::Triangle(Renderer *render) :Shape(render)
{

	vertex = new float[9]
	{
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f,  1.0f, 0.0f,
	};

	SetVertexBuffer(vertex, 3);

	colorVertex = new float[9]
	{
		1.0f,0.0f,0.0f,
		1.0f,0.0f,0.0f,
		1.0f,0.0f,0.0f
	};

	SetColorBuffer(colorVertex, 3);

}
Triangle::~Triangle()
{
	delete[] vertex;
	delete[] colorVertex;
}
void  Triangle::Draw()
{
	DrawMesh(PRIMITIVE_TRIANGLE);
}

