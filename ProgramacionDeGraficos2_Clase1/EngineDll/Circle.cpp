#include "Circle.h"



Circle::Circle(Renderer * renderer):Shape(renderer)
{
	cantVetex = 100.0f;
	vertex = SetVertexPosition(cantVetex, 3.0f);
	SetVertexBuffer(vertex, cantVetex);
	vertexColors = SetVertexColors(cantVetex);
	SetColorBuffer(vertexColors, cantVetex);
}


Circle::~Circle()
{
}



float * Circle::SetVertexPosition(int cantVertex, int radius) 
{
	vertex = new float[cantVertex * 3];
	vertex[0] = 0.0f;
	vertex[1] = 0.0f;
	vertex[2] = 0.0f;
	float degrees =  360.0f / (cantVertex - 2.0f);
	float auxAngle = 0.0;
	for (int i = 3; i < cantVertex * 3; i+=3)
	{
		vertex[i] = cos(auxAngle) * radius;
		vertex[i + 1] = sin(auxAngle) * radius;
		vertex[i + 2] = 0.0f;
		auxAngle += degrees * 3.1415f / 180.0f;
	}

	return vertex;
}

float * Circle::SetVertexColors(int cantVertex)
{
	vertexColors = new float[cantVertex * 3];
	for (int i = 0; i < cantVertex * 3; i++)
	{
		if (i % 2 == 0)
		{
			vertexColors[i] = 1.0f;
		}
		else
		{
			vertexColors[i] = 0.0f;
		}
	}
	return vertexColors;
}

void Circle::SetColorBuffer(float * vertexColor, int cant)
{
	colorBuffer = renderer->GenerateColorBuffer(vertexColor, sizeof(float) * cant * 3);
}

void Circle::Draw()
{
	renderer->LoadIdentityMatrix();
	renderer->SetModel(model);

	if (material != NULL)
	{
		material->Bind();
		material->SetMatrixProperty("ModelViewProjectionMatrix", renderer->GetModelViewProjectionMatrix());
	}
	renderer->EnableVertexAttribute(0);
	renderer->EnableVertexAttribute(1);
	renderer->BindBuffer(vertexBuffer, 0);
	renderer->BindBuffer(colorBuffer, 1);
	renderer->DrawArrayBuffers(PRIMITIVE_TRIANGLE_FAN, cantVetex);
	renderer->DisableVertexAttribute(0);
	renderer->DisableVertexAttribute(1);
}
