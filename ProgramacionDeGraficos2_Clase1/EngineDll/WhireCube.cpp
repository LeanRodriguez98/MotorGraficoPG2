#include "WhireCube.h"
#include <GLFW/glfw3.h>
WhireCube::WhireCube(Renderer * _renderer) : Shape(_renderer)
{
}


WhireCube::~WhireCube()
{
}


void WhireCube::Draw() 
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	renderer->LoadIdentityMatrix();
	renderer->MultiplyModelMatrix(model);

	if (material != NULL) {
		material->Bind();
		material->SetMatrixProperty("WVP", renderer->GetModelViewProjectionMatrix());
	}
	renderer->EnableVertexAttribute(0);
	renderer->EnableVertexAttribute(1);
	renderer->BindBuffer(vertexBufferID, 0);
	renderer->BindColorBuffer(0, 1);
	renderer->DrawArrayBuffers(vertexCount, 0);
	renderer->DisableVertexAttribute(0);
	renderer->DisableVertexAttribute(1);

	
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

}