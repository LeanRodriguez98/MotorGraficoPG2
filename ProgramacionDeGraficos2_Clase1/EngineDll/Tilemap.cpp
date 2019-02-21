#include "Tilemap.h"

Tilemap* Tilemap::instance = 0;
Tilemap * Tilemap::GetInstance()
{
	return instance;
}

Tilemap::Tilemap(Renderer* rend, float width, float height, const char* filename, float cantTilesX, float cantTilesY)
	: Shape(rend), mapWidth(width), mapHeight(height), cantX(cantTilesX), cantY(cantTilesY)
{
	
	

	vertexCount = width * height * 4 * 3;
	cantUVvertex = width * height * 4 * 2;
	
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{

			int col = j * 2;
			int row = i * 2;

			vertexArrayPos.push_back(-10.0f + col);
			vertexArrayPos.push_back(10.0f - row);
			vertexArrayPos.push_back(0.0f);

			vertexArrayPos.push_back(-10.0f + col);
			vertexArrayPos.push_back(8.0f - row);
			vertexArrayPos.push_back(0.0f);

			vertexArrayPos.push_back(-8.0f + col);
			vertexArrayPos.push_back(8.0f - row);
			vertexArrayPos.push_back(0.0f);

			vertexArrayPos.push_back(-8.0f + col);
			vertexArrayPos.push_back(10.0f - row);
			vertexArrayPos.push_back(0.0f);
		}
	}
	float* p = &vertexArrayPos[0];

	
	mapIds = new vector<int>();
	LoadMapIDs(filename);

	bidimensionalIDs = vector<vector<int>>(height, vector<int>(width));
	UpdateTilemap();

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



void Tilemap::DrawMesh(int drawType)
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
	renderer->DrawArrayBuffers(vertexCount, drawType);
	renderer->DisableVertexAttribute(0);
	renderer->DisableVertexAttribute(1);
}

void Tilemap::Draw()
{
	DrawMesh(PRIMITIVE_QUAD);
}

void Tilemap::LoadMapIDs(const char* file)
{
	string buffer;
	ifstream tileFile(file);

	while (getline(tileFile, buffer, ','))
	{
		mapIds->push_back(stoi(buffer));
	}
}

void Tilemap::LoadUVs()
{
	float textureW = 1 / cantX;
	float textureH = 1 / cantY;

	int idIndex = 0;

	for (int i = 0; i < cantUVvertex; i = i + 8)
	{
		// Coordenada 1
		textureUVvertex[i] = 0.0f;
		textureUVvertex[i + 1] = 1.0f;

		// Coordenada 2
		textureUVvertex[i + 2] = 0.0f;
		textureUVvertex[i + 3] = 1.0f - textureH;

		// Coordenada 3
		textureUVvertex[i + 4] = textureW;
		textureUVvertex[i + 5] = 1.0f - textureH;

		// Coordenada 4
		textureUVvertex[i + 6] = textureW;
		textureUVvertex[i + 7] = 1.0f;

		int row = 0;
		int column = mapIds->at(idIndex);

		while (column >= cantX)
		{
			column -= cantX;
			row++;
		}

		// Coordenada 1
		textureUVvertex[i] += textureW * column;
		textureUVvertex[i + 1] -= textureH * row;

		// Coordenada 2
		textureUVvertex[i + 2] += textureW * column;
		textureUVvertex[i + 3] -= textureH * row;

		// Coordenada 3
		textureUVvertex[i + 4] += textureW * column;
		textureUVvertex[i + 5] -= textureH * row;

		// Coordenada 4
		textureUVvertex[i + 6] += textureW * column;
		textureUVvertex[i + 7] -= textureH * row;

		idIndex++;
	}
}

void Tilemap::SetTilemapVertex(float* vertex, int cant)
{
	vertexBufferID = renderer->GenerateBuffer(vertex, sizeof(float) * cant);
}

void Tilemap::UpdateTilemap()
{
	int count = 0;

	for (int i = 0; i < mapHeight; i++)
	{
		for (int j = 0; j < mapWidth; j++)
		{
			bidimensionalIDs[i][j] = mapIds->at(count);
			count++;
		}
	}
}

bool Tilemap::NextTileIsCollider(float x, float y)
{
	int tileID;

	x = (x - GetTranslationX());
	y = -(y + GetTranslationY());

	if (x >= 0 && y >= 0)
	{
		int col = x / 2.0f;
		int row = y / 2.0f;

		std::cout << "x: " << x << " - y: " << y << " - col: " << col << " - row: " << row << endl;

		int temp = indexes.size();
		if (col >= 0 && col < indexes[0].size() && row >= 0 && row < temp)
		{
			tileID = indexes[row][col];
			for (vector<int>::iterator it = tilesWithCollides.begin(); it < tilesWithCollides.end(); it++)
			{
				if (*it == tileID)
				{
					return true;
				}
			}
		}
	}
	return false;
}
void Tilemap::SetColliderTiles(vector<int> v)
{
	tilesWithCollides = v;
}
float Tilemap::GetTileX(float x)
{
	int col = (x - GetTranslationX()) / 2.0f;
	return col * 2.0f + GetTranslationX();
}
float Tilemap::GetTileY(float y)
{
	int row = (y + GetTranslationY()) / 2.0f;

	return row * 2.0f- GetTranslationY();
}