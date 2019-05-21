#include "Mesh.h"
#pragma warning(disable:4996)

Mesh::Mesh(string _modelPath, string _texturePath, Renderer* _renderer) : Shape(_renderer)
{
	this->texturePath = new char[_texturePath.size() + 1];
	_texturePath.copy(this->texturePath, _texturePath.size() + 1);
	this->texturePath[_texturePath.size()] = '\0';

	MeshLoader::GetInstance()->LoadMesh(_modelPath, _texturePath, meshEntries, meshTextures, _renderer);

	for (int i = 0; i < meshTextures.size(); i++)
	{
		buffersTextureID.push_back(_renderer->GenerateTextureBuffer(meshTextures[i].width, meshTextures[i].height, meshTextures[i].data));
	}
}
Mesh::~Mesh()
{
}

void Mesh::Update()
{
	Entity::UpdateModel();
}

void Mesh::Draw()
{
	renderer->LoadIdentityMatrix();
	renderer->MultiplyModelMatrix(model);
	if (material != NULL) {
		material->Bind();
		material->SetMatrixProperty("WVP", renderer->GetModelViewProjectionMatrix());
		material->BindTexture("myTextureSampler", buffersTextureID[0]);
	}
	renderer->EnableVertexAttribute(0);
	renderer->EnableVertexAttribute(1);
	for (int i = 0; i < meshEntries.size(); i++) {

		renderer->BindBuffer(meshEntries[i].vertexBuffer, 0);
		renderer->BindTextureBuffer(meshEntries[i].uvBuffer, 1);
		renderer->BindMeshBuffer(meshEntries[i].indexBuffer);
		renderer->DrawIndexBuffer(meshEntries[i].cantIndex);
	}
	renderer->DisableVertexAttribute(0);
	renderer->DisableVertexAttribute(1);
}
