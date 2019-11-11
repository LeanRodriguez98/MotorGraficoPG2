#include "Mesh.h"

Mesh::Mesh(Renderer * _renderer,  const char * _textureFile, Camera * _camera) :Component(_renderer)
{
	type = ComponentType::MeshRendererComponent;
	textureFile = _textureFile;
	meshData = new MeshData;
	meshEntry = new MeshEntry();
	camera = _camera;
	boundingBox3D = new BoundingBox3D(_renderer);
}

void Mesh::SetMeshEntry(MeshEntry * _meshEntry)
{
	meshEntry = _meshEntry;
	meshData->vertexCount = meshEntry->vertexArray->size();
	meshData->indexCount = meshEntry->indexArray->size();
	meshData->UVCount = meshEntry->uvArray->size();
	meshData->vertex = new float[meshData->vertexCount];
	for (int i = 0; i < meshData->vertexCount; i++) 
	{
		meshData->vertex[i] = meshEntry->vertexArray->at(i);
	}
	meshData->vertexBufferID = renderer->GenerateBuffer(meshData->vertex, sizeof(float)* meshData->vertexCount);
	meshData->UVVertex = new float[meshData->UVCount];
	for (int i = 0; i < meshData->UVCount; i++)
	{
		meshData->UVVertex[i] = meshEntry->uvArray->at(i);
	}
	meshData->uvBufferID = renderer->GenerateBuffer(meshData->UVVertex, sizeof(float)* meshData->UVCount);
	meshData->index = new unsigned int[meshData->indexCount];
	for (int i = 0; i < meshData->indexCount; i++) 
	{
		meshData->index[i] = meshEntry->indexArray->at(i);
	}
	meshData->indexBufferID = renderer->GenerateMeshBuffer(meshData->index, sizeof(int) * meshData->indexCount);
	meshData->material = new Material();
	meshData->programID = meshData->material->LoadShaders("texturevertexshader.txt", "texturefragmentshader.txt");
	BMPTexture = TextureImporter::LoadBMP(textureFile);
	meshData->textureBufferID = renderer->GenerateTextureBuffer(BMPTexture.width, BMPTexture.height, BMPTexture.data);
	meshData->material->BindTexture("myTextureSampler", meshData->textureBufferID);
}

void Mesh::SetBSP( Node * node)
{
	isBsp = true;
	bspForward = normalize((vec3)(node->GetRotationMatrix() * vec4(0.0f, 0.0f, 1.0f, 0.0f)));

	camera->AddBSP(this, node->GetTranslation());
}

bool Mesh::GetIsBsp()
{
	return isBsp;
}

vec3 Mesh::GetForwardBSP()
{
	return bspForward;
}

void Mesh::Draw()
{
	if(!(camera->BoxInBSP(boundingBox3D) || !camera->BoxInFrustum(boundingBox3D)))
	{
		if (meshData->material != NULL) 
		{
			meshData->material->Bind();
			meshData->material->SetMatrixProperty("WVP", renderer->GetModelViewProjectionMatrix());
		}
		renderer->BindTexture(meshData->textureBufferID, meshData->uvBufferID);
		renderer->EnableVertexAttribute(0);
		renderer->BindBuffer(meshData->vertexBufferID,0);
		renderer->EnableVertexAttribute(1);
		renderer->BindTextureBuffer(meshData->uvBufferID,1);
		renderer->DrawIndexMesh(meshData->indexCount, meshData->indexBufferID);
		renderer->DisableVertexAttribute(0);
		renderer->DisableVertexAttribute(1);
	}
}

MeshEntry * Mesh::GetMeshEntry()
{
	return meshEntry;
}

Mesh::~Mesh() 
{
	delete[] meshData->vertex;
	delete[] meshData->UVVertex;
	delete[] meshData->index;
	delete meshData->material;
	delete meshData;
	delete meshEntry;
}