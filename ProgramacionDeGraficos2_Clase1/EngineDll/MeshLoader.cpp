#include "MeshLoader.h"
// http://ogldev.atspace.co.uk/www/tutorial22/tutorial22.html
MeshLoader * MeshLoader::instance = NULL;

MeshLoader::MeshLoader()
{
}

void MeshLoader::LoadMesh(const string& _modelPath, const string& _texturePath, vector<MeshEntry>& _meshEntries, vector<BMPData>& _meshTextures, Renderer* _renderer)
{
	Importer Importer;
	const aiScene* pScene = Importer.ReadFile(_modelPath.c_str(), aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices);
	if (pScene)
	{
		InitFromScene(pScene, _texturePath, _meshEntries, _meshTextures, _renderer);
	}
	else
	{
		printf("Error parsing '%s': '%s'\n", _modelPath.c_str(), Importer.GetErrorString());
	}
}
void MeshLoader::InitFromScene(const aiScene* _pScene, const string& _texturePath, vector<MeshEntry>& _meshEntries, vector<BMPData>& _meshTextures, Renderer* _renderer)
{
	_meshEntries.resize(_pScene->mNumMeshes);
	_meshTextures.resize(_pScene->mNumMaterials);

	for (int i = 0; i < _meshEntries.size(); i++)
	{
		const aiMesh* paiMesh = _pScene->mMeshes[i];
		InitMesh(i, paiMesh, _meshEntries, _renderer);
	}

	for (int i = 0; i < _pScene->mNumMaterials; i++)
	{
		_meshTextures[i] = TextureImporter::LoadBMP(_texturePath.c_str());
	}
}

void MeshLoader::InitMesh(unsigned int _index, const aiMesh* _paiMesh, vector<MeshEntry>& _meshEntries, Renderer* _renderer)
{

	vector<Vertex> Vertices;
	vector<unsigned int> Indices;

	const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);

	for (int i = 0; i < _paiMesh->mNumVertices; i++)
	{
		const aiVector3D* pPos = &(_paiMesh->mVertices[i]);
		const aiVector3D* pNormal = &(_paiMesh->mNormals[i]);
		const aiVector3D* pTexCoord = _paiMesh->HasTextureCoords(0) ? &(_paiMesh->mTextureCoords[0][i]) : &Zero3D;

		Vertex v(vec3(pPos->x, (float)pPos->y, (float)pPos->z), vec2((float)pTexCoord->x, (float)pTexCoord->y), vec3((float)pNormal->x, (float)pNormal->y, (float)pNormal->z));

		Vertices.push_back(v);
	}

	for (int i = 0; i < _paiMesh->mNumFaces; i++)
	{
		const aiFace& Face = _paiMesh->mFaces[i];
		assert(Face.mNumIndices == 3);
		Indices.push_back(Face.mIndices[0]);
		Indices.push_back(Face.mIndices[1]);
		Indices.push_back(Face.mIndices[2]);
	}

	_meshEntries[_index].Init(Vertices, Indices, _renderer);
}

