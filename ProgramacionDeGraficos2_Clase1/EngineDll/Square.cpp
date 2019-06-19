
#include "Square.h"
Square::Square(Renderer *render) :Shape(render)
{
	vertex = new float[12]
	{
		-1.0f,-1.0f , 0.0f ,
		1.0f,-1.0f , 0.0f ,
		-1.0f, 1.0f , 0.0f ,
		1.0f, 1.0f , 0.0f
	};

	SetVertexBuffer(vertex, 4);

	colorVertex = new float[12]
	{
		1.0f, 1.0f , 1.0f ,
		1.0f, 1.0f , 1.0f ,
		1.0f, 1.0f , 1.0f ,
		1.0f, 1.0f , 1.0f
	};
	SetColorBuffer(colorVertex, 4);
}

Square::~Square()
{
	delete[] vertex;
	delete[] colorVertex;
}

void Square::Draw()
{
	DrawMesh(PRIMITIVE_TRIANGLE_STRIP);
}
