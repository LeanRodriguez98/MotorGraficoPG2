#include "Tilemap.h"


Tilemap::Tilemap(Renderer* _renderer, float _tilemapWidth, float _tilemapHeight, const char* _filename, float _cantTilesX, float _cantTilesY, float _tileOffset, float _tileSize, vector<int>* _colliderTiles): Shape(_renderer)
{
	
	tilemapWidth = _tilemapWidth;
	tilemapHeight = _tilemapHeight;
	cantTilesX = _cantTilesX;
	cantTilesY = _cantTilesY;
	tileOffset = _tileOffset;
	tileSize = _tileSize;
	vertexCount = _tilemapWidth * _tilemapHeight * 4 * 3;
	cantUVvertex = _tilemapWidth * _tilemapHeight * 4 * 2;
	

	mapIds = new vector<int>();
	LoadMapIDs(_filename);
	tilesWithCollides = new vector<int>();
	tilesWithCollides = _colliderTiles;
	tilesColliderData = new vector<TileColliderData>();
	int aux = 0;
	for (int i = 0; i < _tilemapHeight; i++)
	{
		for (int j = 0; j < _tilemapWidth; j++)
		{

			int col = j * 2;
			int row = i * 2;

			vertexArrayPos.push_back(-tileOffset + col);
			vertexArrayPos.push_back(tileOffset - row);
			vertexArrayPos.push_back(0.0f);

			vertexArrayPos.push_back(-tileOffset + col);
			vertexArrayPos.push_back((tileOffset - tileSize) - row);
			vertexArrayPos.push_back(0.0f);

			vertexArrayPos.push_back(-(tileOffset - tileSize) + col);
			vertexArrayPos.push_back((tileOffset - tileSize) - row);
			vertexArrayPos.push_back(0.0f);

			vertexArrayPos.push_back(-(tileOffset - tileSize) + col);
			vertexArrayPos.push_back(tileOffset - row);
			vertexArrayPos.push_back(0.0f);

			for (int k = 0; k < tilesWithCollides->size(); k++)
			{
				if (mapIds->at(aux) == tilesWithCollides->at(k))
				{
					TileColliderData colliderAux;
				
					colliderAux.positionY = (tileOffset - row) - tileSize;
					colliderAux.positionX = (-tileOffset + col);
					//cout << colliderAux.positionX << " - " << colliderAux.positionY << endl;
					colliderAux.height = tileSize;
					colliderAux.width = tileSize;
					tilesColliderData->push_back(colliderAux);
				}
			}

			aux++;
		
		}
	}
	float* p = &vertexArrayPos[0];

	textureUVvertex = new float[cantUVvertex];
	LoadUVs();

	SetTilemapVertex(p, vertexCount);

	SetTextures(textureUVvertex, cantUVvertex);
}

Tilemap::~Tilemap()
{
}

void Tilemap::SetTextures(float* vertex, int cant)
{
	UVBufferId = renderer->GenerateBuffer(vertex, sizeof(float)* cant);
}

void Tilemap::LoadTexture(const char* name)
{
	header = TextureImporter::LoadBMP(name);
	textureBufferId = renderer->GenerateTextureBuffer(header.width, header.height, header.data);
}



void Tilemap::DrawMesh(int _drawType)
{
	renderer->LoadIdentityMatrix();
	renderer->MultiplyModelMatrix(model);


	if (material != NULL) {
		material->Bind();
		material->SetMatrixProperty("WVP", renderer->GetModelViewProjectionMatrix());
		material->BindTexture("myTextureSampler", textureBufferId);
	}

	renderer->EnableVertexAttribute(0);
	renderer->EnableVertexAttribute(1);
	renderer->BindBuffer(vertexBufferID, 0);
	renderer->BindTextureBuffer(UVBufferId, 1);
	renderer->DrawArrayBuffers(vertexCount, _drawType);
	renderer->DisableVertexAttribute(0);
	renderer->DisableVertexAttribute(1);
}

void Tilemap::Draw()
{
	DrawMesh(PRIMITIVE_QUAD);
}

void Tilemap::LoadMapIDs(const char* _file)
{
	string buffer;
	ifstream tileFile(_file);

	while (getline(tileFile, buffer, ','))
	{
		mapIds->push_back(stoi(buffer));
	}
}

void Tilemap::LoadUVs()
{
	float textureW = 1 / cantTilesX;
	float textureH = 1 / cantTilesY;

	int idIndex = 0;

	for (int i = 0; i < cantUVvertex; i = i + 8)
	{
		textureUVvertex[i] = 0.0f;
		textureUVvertex[i + 1] = 1.0f;

		textureUVvertex[i + 2] = 0.0f;
		textureUVvertex[i + 3] = 1.0f - textureH;

		textureUVvertex[i + 4] = textureW;
		textureUVvertex[i + 5] = 1.0f - textureH;

		textureUVvertex[i + 6] = textureW;
		textureUVvertex[i + 7] = 1.0f;

		int row = 0;
		int column = mapIds->at(idIndex);

		while (column >= cantTilesX)
		{
			column -= cantTilesX;
			row++;
		}

		textureUVvertex[i] += textureW * column;
		textureUVvertex[i + 1] -= textureH * row;

		textureUVvertex[i + 2] += textureW * column;
		textureUVvertex[i + 3] -= textureH * row;

		textureUVvertex[i + 4] += textureW * column;
		textureUVvertex[i + 5] -= textureH * row;

		textureUVvertex[i + 6] += textureW * column;
		textureUVvertex[i + 7] -= textureH * row;

		idIndex++;
	}
}

void Tilemap::SetTilemapVertex(float* _vertex, int _cant)
{
	vertexBufferID = renderer->GenerateBuffer(_vertex, sizeof(float) * _cant);
}


bool Tilemap::NextTileIsCollider(float _playerTranslationX, float _playerTranslationY, float _playerHeight, float _playerWidht)
{

	float col = (((_playerTranslationX - GetTranslationX()) / tileSize) * tileSize) + GetTranslationX();
	float row = (((_playerTranslationY + GetTranslationY()) / tileSize) * tileSize) - GetTranslationY();

	for (int i = 0; i < tilesColliderData->size(); i++)
	{
		if (((col + (_playerWidht/2)) >= tilesColliderData->at(i).positionX) && ((col - (_playerWidht / 2)) <= tilesColliderData->at(i).positionX + tilesColliderData->at(i).width) && (row + (_playerHeight/2)  >= tilesColliderData->at(i).positionY) && (row - (_playerHeight / 2) <= tilesColliderData->at(i).positionY + tilesColliderData->at(i).height))
		{
			return true;
		}
	}
	return false;
}
