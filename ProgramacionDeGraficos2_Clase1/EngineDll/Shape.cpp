#include "Shape.h"



Shape::Shape(Renderer * renderer) : Entity(renderer)
{
	material = NULL;
	vertex = NULL;
	vertexBuffer = -1;
}


Shape::~Shape()
{
}

void Shape::SetVertexBuffer(float * vertex, int cant)
{
	vertexBuffer = renderer->GenerateVertexBuffer(vertex, sizeof(float) * cant * 3);

}

void Shape::SetMaterial(Material * _material)
{
	material = _material;
}