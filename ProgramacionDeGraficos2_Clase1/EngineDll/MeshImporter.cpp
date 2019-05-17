#include "MeshImporter.h"

MeshImporter * MeshImporter::instance = NULL;

MeshImporter::MeshImporter()
{
}


MeshImporter::~MeshImporter()
{
}



void MeshImporter::Clear(vector<BMPData*>& textures)
{
	for (int i = 0; i < textures.size(); i++)
	{
		delete textures[i];
		textures[i] = NULL;
	}
}

float * MeshImporter::GetMeshVertex(string path) 
{
	float * v;
	Assimp::Importer importer;
	const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		cout << "ERROR::ASSIMP::" << importer.GetErrorString() << endl;
		return;
	}

	aiVector3D * aivec = scene->mMeshes[0]->mVertices;
	ai_real x = aivec->x;
	//x.   
}

