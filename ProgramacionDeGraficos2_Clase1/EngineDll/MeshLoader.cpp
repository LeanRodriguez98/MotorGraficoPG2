#include "MeshLoader.h"
#include "Mesh.h"

// http://ogldev.atspace.co.uk/www/tutorial22/tutorial22.html

MeshLoader * MeshLoader::instance = NULL;

MeshLoader::MeshLoader()
{

}

void MeshLoader::LoadMesh(const char * _modelPath, const char * _texturePath, Node * _rootNode, Renderer* _renderer, Camera * _camera)
{

	boundingBoxMin = vec3(INT_MAX, INT_MAX, INT_MAX);
	boundingBoxMax = vec3(INT_MIN, INT_MIN, INT_MIN);
	Importer Importer;
	const aiScene* pScene = Importer.ReadFile(_modelPath, aiProcess_CalcTangentSpace | aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_SortByPType);

	if (!pScene || !pScene->HasMeshes())
	{
		return;
	}

	ProcessNodes(_texturePath, _rootNode, pScene->mRootNode, pScene, _renderer, _camera);
	GenerateBoundingBox(_rootNode);

}


void MeshLoader::ProcessNodes(const char * _texturePath, Node * _rootNode, aiNode * _aiNode, const aiScene * _aiScene, Renderer * _renderer, Camera * _camera)
{
	for (int i = 0; i < (int)_aiNode->mNumMeshes; i++)
	{
		Mesh * mesh = new Mesh(_renderer, _texturePath, _camera);
		Node * child = new Node(_renderer);
		child->AddComponent((Component *)mesh);
		InitMesh(_aiScene->mMeshes[_aiNode->mMeshes[i]], mesh, (Mesh *)child->GetComponentByType(ComponentType::MeshRendererComponent));
		_rootNode->AddChild(child);
		SetNodeTransform(_aiNode, child);
		TrySetBspNode(_aiScene->mMeshes[_aiNode->mMeshes[i]], child, mesh);
	}

	for (int i = 0; i < (int)_aiNode->mNumChildren; i++)
	{
		ProcessNodes(_texturePath, _rootNode, _aiNode->mChildren[i], _aiScene, _renderer, _camera);
	}
}

void MeshLoader::InitMesh(const aiMesh* _paiMesh, Mesh * _mesh, Mesh * _childMesh)
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

		if (pPos->x < boundingBoxMin.x)
			boundingBoxMin.x = pPos->x;
		if (pPos->x > boundingBoxMax.x)
			boundingBoxMax.x = pPos->x;
		if (pPos->y < boundingBoxMin.y)
			boundingBoxMin.y = pPos->y;
		if (pPos->y > boundingBoxMax.y)
			boundingBoxMax.y = pPos->y;
		if (pPos->z < boundingBoxMin.z)
			boundingBoxMin.z = pPos->z;
		if (pPos->z > boundingBoxMax.z)
			boundingBoxMax.z = pPos->z;

		mesh->vertexArray->push_back(pPos->x);
		mesh->vertexArray->push_back(pPos->y);
		mesh->vertexArray->push_back(pPos->z);
		mesh->uvArray->push_back(pTexCoord->x);
		mesh->uvArray->push_back(pTexCoord->y);
	}

	for (unsigned int i = 0; i < _paiMesh->mNumFaces; i++)
	{
		const aiFace& Face = _paiMesh->mFaces[i];
		assert(Face.mNumIndices == 3);
		mesh->indexArray->push_back(Face.mIndices[0]);
		mesh->indexArray->push_back(Face.mIndices[1]);
		mesh->indexArray->push_back(Face.mIndices[2]);
	}

	_mesh->SetMeshEntry(mesh);
}

void MeshLoader::GenerateBoundingBox(Node * _rootNode)
{
	vec3 boundingBoxVertices[CANT_BOUNDING_BOX_VERTEX] =
	{
		vec3(boundingBoxMin.x, boundingBoxMin.y, boundingBoxMin.z),
		vec3(boundingBoxMin.x, boundingBoxMax.y, boundingBoxMin.z),
		vec3(boundingBoxMin.x, boundingBoxMin.y, boundingBoxMax.z),
		vec3(boundingBoxMin.x, boundingBoxMax.y, boundingBoxMax.z),
		vec3(boundingBoxMax.x, boundingBoxMin.y, boundingBoxMin.z),
		vec3(boundingBoxMax.x, boundingBoxMax.y, boundingBoxMin.z),
		vec3(boundingBoxMax.x, boundingBoxMin.y, boundingBoxMax.z),
		vec3(boundingBoxMax.x, boundingBoxMax.y, boundingBoxMax.z)
	};


	for (int i = 0; i < _rootNode->GetChildsVector()->size(); i++)
	{
		if (_rootNode->GetChildByIndex(i)->GetComponentByType(ComponentType::MeshRendererComponent) != nullptr)
		{
			((Mesh *)_rootNode->GetChildByIndex(i)->GetComponentByType(ComponentType::MeshRendererComponent))->boundingBox3D->SetVertex(boundingBoxVertices);
		}
	}
}

void MeshLoader::SetNodeTransform(aiNode * _aiNode, Node * _node)
{
	aiVector3D aiScaling;
	aiVector3D aiPosition;
	aiQuaternion aiRotation;

	_aiNode->mTransformation.Decompose(aiScaling, aiRotation, aiPosition);
	cout << "Loading: " << _aiNode->mName.C_Str() << endl << endl;;
	cout << "Position: " << "( " << aiPosition.x << " , " << aiPosition.y << " , " << aiPosition.z << " )" << endl;
	cout << "Rotation: " << "( " << aiRotation.x << " , " << aiRotation.y << " , " << aiRotation.z << " , " << aiRotation.w << " )" << endl;
	cout << "Scale: " << "( " << aiScaling.x << " , " << aiScaling.y << " , " << aiScaling.z << " )" << endl;
	cout << endl;
	_node->SetRotationMatrix(aiRotation.x, aiRotation.y, aiRotation.z, aiRotation.w);
	_node->SetTranslation(aiPosition.x, aiPosition.y, aiPosition.z);
	_node->SetScale(aiScaling.x, aiScaling.y, aiScaling.z);
}

void MeshLoader::TrySetBspNode(const aiMesh * _paiMesh, Node * _node, Mesh * _meshComponent)
{
	string meshName = _paiMesh->mName.C_Str();
	if (meshName.compare(0, 5, "Plane") == 0)
	{
		cout << _paiMesh->mName.C_Str() << " it's a BSP plane" << endl << endl;
		_meshComponent->SetBSP(_node);
	}
}


