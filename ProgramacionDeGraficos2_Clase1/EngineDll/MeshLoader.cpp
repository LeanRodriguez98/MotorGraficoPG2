#include "MeshLoader.h"
// http://ogldev.atspace.co.uk/www/tutorial22/tutorial22.html
MeshLoader * MeshLoader::instance = NULL;

MeshLoader::MeshLoader()
{
}





void MeshLoader::Clear(vector<BMPData*>& textures)
{
	for (int i = 0; i < textures.size(); i++)
	{
		if (textures[i] != NULL)
		{
			delete textures[i];
			textures[i] = NULL;
		}
	}
}


bool MeshLoader::LoadMesh(const string& Filename, const string& texturePath, vector<MeshEntry>& m_Entries, vector<BMPData*>& m_Textures)
{
	// Release the previously loaded mesh (if it exists)
	Clear(m_Textures);// QUITAR * A BMPData*

	bool Ret = false;
	Assimp::Importer Importer;

	const aiScene* pScene = Importer.ReadFile(Filename.c_str(), aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices);

	if (pScene) {
		Ret = InitFromScene(pScene, Filename, m_Entries, m_Textures);
	}
	else {
		printf("Error parsing '%s': '%s'\n", Filename.c_str(), Importer.GetErrorString());
	}

	return Ret;
}

bool MeshLoader::InitFromScene(const aiScene* pScene, const string& Filename, vector<MeshEntry>& m_Entries, vector<BMPData*>& m_Textures)
{
	m_Entries.resize(pScene->mNumMeshes);
	m_Textures.resize(pScene->mNumMaterials);

	// Initialize the meshes in the scene one by one
	for (unsigned int i = 0; i < m_Entries.size(); i++) {
		const aiMesh* paiMesh = pScene->mMeshes[i];
		InitMesh(i, paiMesh, m_Entries);
	}
	return true;
}

void MeshLoader::InitMesh(unsigned int Index, const aiMesh* paiMesh, vector<MeshEntry>& m_Entries)
{

	vector<Vertex> Vertices;
	vector<unsigned int> Indices;

	const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);

	for (unsigned int i = 0; i < paiMesh->mNumVertices; i++) {
		const aiVector3D* pPos = &(paiMesh->mVertices[i]);
		const aiVector3D* pNormal = &(paiMesh->mNormals[i]);
		const aiVector3D* pTexCoord = paiMesh->HasTextureCoords(0) ? &(paiMesh->mTextureCoords[0][i]) : &Zero3D;

		Vertex v(vec3(pPos->x, pPos->y, pPos->z),
			vec2(pTexCoord->x, pTexCoord->y),
			vec3(pNormal->x, pNormal->y, pNormal->z));

		Vertices.push_back(v);
	}

	for (unsigned int i = 0; i < paiMesh->mNumFaces; i++) {
		const aiFace& Face = paiMesh->mFaces[i];
		assert(Face.mNumIndices == 3);
		Indices.push_back(Face.mIndices[0]);
		Indices.push_back(Face.mIndices[1]);
		Indices.push_back(Face.mIndices[2]);
	}

	m_Entries[Index].Init(Vertices, Indices);
}


