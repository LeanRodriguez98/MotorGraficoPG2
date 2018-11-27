#include "Shape.h"



Shape::Shape(Renderer* renderer) : Entity(renderer)
{
	material = NULL;
	vertex = NULL;
	colorVertex = NULL;

	vertexBufferID = -1;
	colorBufferID = -1;

}
Shape::~Shape()
{


}
void Shape::SetVertexBuffer(float* _vertex, int _cant)
{
	vertexCount = _cant;
	vertexBufferID = renderer->GenerateBuffer(_vertex, sizeof(float)* _cant * 3);
}
void Shape::SetColorBuffer(float* _vertex, int _cant)
{
	colorVertexCount = _cant;
	colorBufferID = renderer->GenerateColorBuffer(_vertex, sizeof(float)* _cant * 3);
}


void Shape::SetMaterial(Material* _material)
{
	this->material = _material;
}

void Shape::DrawMesh(int drawType)
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
	renderer->DrawArrayBuffers(vertexCount, drawType);
	renderer->DisableVertexAttribute(0);
	renderer->DisableVertexAttribute(1);
}


