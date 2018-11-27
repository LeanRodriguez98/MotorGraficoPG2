#include "Circle.h"
Circle::Circle(Renderer *render, float _radius, int _cantTriangles) :Shape(render)
{
	cantTriangles = _cantTriangles;
	radius = _radius;
	vertexCount = cantTriangles * 3;
	float degrees = 360.0f / cantTriangles;
	float auxAngle = 0.0f;

	vertex = new float[vertexCount];

	for (int i = 0; i < vertexCount; i += 3)
	{
		vertex[i] = cos(auxAngle) * radius;
		vertex[i + 1] = sin(auxAngle) * radius;
		vertex[i + 2] = 0.0f;
		auxAngle += degrees * 3.1415f / 180.0f;
	}
	SetVertexBuffer(vertex, cantTriangles);
	SetColorBuffer(vertex, cantTriangles);
}

Circle::~Circle()
{
	delete[] vertex;
}
void Circle::Draw()
{
	DrawMesh(PRIMITIVE_TRIANGLE_FAN);
}
