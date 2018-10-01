#include "Square.h"

Square::Square(Renderer * renderer) : Shape(renderer)
{
	material = NULL;
	vertex = NULL;
	vertexColors = NULL;
	vertexBuffer = -1;
	colorBuffer = -1;

	vertex = new float[12]{
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		-1.0f,  1.0f, 0.0f,
		1.0f, 1.0f, 0.0f
	};

	vertexColors = new float[12]{
		1.0f,  0.0f,  0.0f,
		0.0f,  1.0f,  0.0f,
		0.0f,  0.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
	};

	SetVertexBuffer(vertex, 4);
	SetColorBuffer(vertexColors, 4);
}

Square::~Square()
{
}



void Square::SetColorBuffer(float * vertexColor, int cant)
{
	colorBuffer = renderer->GenerateColorBuffer(vertexColor, sizeof(float) * cant * 3);
}

void Square::Draw()
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
	renderer->BindBuffer(vertexBuffer,0);
	renderer->BindBuffer(colorBuffer, 1);
	renderer->DrawArrayBuffers(PRIMITIVE_TRIANGLE_STRIP,4);
	renderer->DisableVertexAttribute(0);
	renderer->DisableVertexAttribute(1);
}

