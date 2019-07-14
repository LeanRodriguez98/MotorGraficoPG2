#include "MeshLoader.h"
#include "Mesh.h"

// http://ogldev.atspace.co.uk/www/tutorial22/tutorial22.html

MeshLoader * MeshLoader::instance = NULL;

MeshLoader::MeshLoader()
{
}

void MeshLoader::LoadMesh(const char * _modelPath, const char * _texturePath, Node * _rootNode, Renderer* _renderer)
{
	Importer Importer;
	const aiScene* pScene = Importer.ReadFile(_modelPath, aiProcess_CalcTangentSpace | aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_SortByPType);

	if (!pScene)
	{
		return;
	}

	if (!pScene->HasMeshes())
	{
		return;
	}

	ProcessNodes(_modelPath, _texturePath, _rootNode, pScene->mRootNode, pScene, _renderer);
}


void MeshLoader::ProcessNodes(const char * _modelPath, const char * _texturePath, Node * _rootNode,	aiNode * _aiNode, const aiScene * _aiScene, Renderer * _renderer)
{
	for (int i = 0; i < (int)_aiNode->mNumMeshes; i++) 
	{
		Mesh * mesh = new Mesh(_renderer, _modelPath, _texturePath, _rootNode);
		InitMesh(_aiScene->mMeshes[_aiNode->mMeshes[i]], mesh);
		Node * child = new Node(_renderer);
		child->AddComponent((Component*)mesh);
		_rootNode->AddChild(child);
	}

	for (int i = 0; i < (int)_aiNode->mNumChildren; i++) 
	{
		ProcessNodes(_modelPath, _texturePath, _rootNode, _aiNode->mChildren[i], _aiScene, _renderer);
	}
}

void MeshLoader::InitMesh(const aiMesh* _paiMesh, Mesh * _mesh)
{
	MeshEntry * mesh = _mesh->GetMeshEntry();
	mesh->vertexArray = new std::vector<float>();
	mesh->uvArray = new std::vector<float>();
	mesh->indexArray = new std::vector<unsigned int>();

	const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);

	for (unsigned int i = 0; i < _paiMesh->mNumVertices; i++) {
		const aiVector3D* pPos = &(_paiMesh->mVertices[i]);
		const aiVector3D* pNormal = &(_paiMesh->mNormals[i]);
		const aiVector3D* pTexCoord = _paiMesh->HasTextureCoords(0) ? &(_paiMesh->mTextureCoords[0][i]) : &Zero3D;

		mesh->vertexArray->push_back(pPos->y);
		mesh->vertexArray->push_back(pPos->x);
		mesh->vertexArray->push_back(pPos->z);
		mesh->uvArray->push_back(pTexCoord->x);
		mesh->uvArray->push_back(pTexCoord->y);
	}

	for (unsigned int i = 0; i < _paiMesh->mNumFaces; i++) {
		const aiFace& Face = _paiMesh->mFaces[i];
		assert(Face.mNumIndices == 3);
		mesh->indexArray->push_back(Face.mIndices[0]);
		mesh->indexArray->push_back(Face.mIndices[1]);
		mesh->indexArray->push_back(Face.mIndices[2]);
	}

	_mesh->SetMeshEntry(mesh);
}
