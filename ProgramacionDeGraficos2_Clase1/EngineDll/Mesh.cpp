#include "Mesh.h"



Mesh::Mesh(Renderer *render) :Shape(render)
{
	vertex = new float[24]
	{
		-1.0, -1.0, 1.0,
		1.0, -1.0, 1.0,
		1.0, 1.0, 1.0,
		-1.0, 1.0, 1.0,
		-1.0, -1.0, -1.0,
		1.0, -1.0, -1.0,
		1.0, 1.0, -1.0,
		-1.0, 1.0, -1.0
	};
	SetVertexBuffer(vertex, 8);

	colorVertex = new float[24]
	{
	 1.0, 0.0, 0.0,
	 0.0, 1.0, 0.0,
	 0.0, 0.0, 1.0,
	 1.0, 1.0, 1.0,
	  1.0, 0.0, 0.0,
	  0.0, 1.0, 0.0,
	  0.0, 0.0, 1.0,
	 1.0, 1.0, 1.0
	};
	SetColorBuffer(colorVertex, 8);

	indexBuffer = new unsigned int[36]
	{
		0, 1, 2,
		2, 3, 0,
		1, 5, 6,
		6, 2, 1,
		7, 6, 5,
		5, 4, 7,
		4, 0, 3,
		3, 7, 4,
		4, 5, 1,
		1, 0, 4,
		3, 2, 6,
		6, 7, 3
	};
	SetIndexBuffer(indexBuffer, 36);

}


Mesh::~Mesh()
{
}

void Mesh::Draw()
{
	DrawMesh(PRIMITIVE_TRIANGLE);
}

void Mesh::DrawMesh(int drawType)
{
	renderer->LoadIdentityMatrix();
	renderer->MultiplyModelMatrix(model);

	if (material != NULL) {
		material->Bind();
		material->SetMatrixProperty("WVP", renderer->GetModelViewProjectionMatrix());
	}
	renderer->EnableVertexAttribute(0);
	renderer->EnableVertexAttribute(1);
	renderer->BindBuffer(vertexBufferID, 0);
	renderer->BindColorBuffer(colorBufferID, 1);
	renderer->BindMeshBuffer(indexBufferID);
	renderer->DrawIndexBuffer(vertexCount);

	renderer->DisableVertexAttribute(0);
	renderer->DisableVertexAttribute(1);
}
