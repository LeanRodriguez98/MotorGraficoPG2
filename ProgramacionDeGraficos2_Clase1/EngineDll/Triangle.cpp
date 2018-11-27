/*#include "Triangle.h"

Triangle::Triangle(Renderer * renderer) : Shape(renderer)
{
	material = NULL;
	vertex = NULL;
	vertexBuffer = -1;

	vertex = new float[9]{
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f,  1.0f, 0.0f,
	};

	SetVertexBuffer(vertex, 3);
}

Triangle::~Triangle()
{
}


void Triangle::Draw()
{
	renderer->LoadIdentityMatrix();
	renderer->SetModel(model);

	if (material != NULL)
	{
		material->Bind();
		material->SetMatrixProperty("ModelViewProjectionMatrix", renderer->GetModelViewProjectionMatrix());
	}
	renderer->EnableVertexAttribute(0);
	renderer->BindBuffer(vertexBuffer, 0);
	renderer->DrawArrayBuffers(PRIMITIVE_TRIANGLE,3);
	renderer->DisableVertexAttribute(0);
}
*/

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

