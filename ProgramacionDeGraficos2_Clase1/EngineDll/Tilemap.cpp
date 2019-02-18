#include "Tilemap.h"

Tilemap::Tilemap(Renderer* _renderer, const char* _tileMapName, float _levelWidth, float _levelHeight, Material* _material, const char* _tilesSheetName, float _tileSheetTilesX, float _tileSheetTilesY)
{

	tileMap = _tileMapName;
	tileMapsIds = new vector<int>();
	levelWidth = _levelWidth;
	levelHeight = _levelHeight;
	tilesMaterial = _material;
	tileSheetTilesX = _tileSheetTilesX;
	tileSheetTilesY = _tileSheetTilesY;
	texture = _tilesSheetName;
	renderer = _renderer;
	LoadTileMap();
	collisionableTileMapsIds = new vector<int>();
	tiles = new vector<Tile*>();

	ChargeTiles();

}

Tilemap::~Tilemap()
{
}

void Tilemap::ChargeTiles()
{
	for (int i = 0; i < tileMapsIds->size(); i++)
	{
		Tile* x = new Tile(renderer, tileMapsIds->at(i), tileSheetTilesX, tileSheetTilesY);
		x->SetMaterial(tilesMaterial);
		x->LoadTileTexture(texture);
		tiles->push_back(x);
	}
}

void Tilemap::LoadTileMap()
{
	string auxBuffer;
	ifstream tileFile(tileMap);

	while (getline(tileFile, auxBuffer, ','))
	{
		tileMapsIds->push_back(stoi(auxBuffer));
	}
}

void Tilemap::DrawTileMap()
{
	int x = -(levelWidth - 1);
	int y = levelHeight - 1;

	for (int i = 0; i < tiles->size(); i++)
	{
		tiles->at(i)->SetTranslation(x, y, 0);
		tiles->at(i)->Draw();
		x += 2;
		if (x > levelWidth)
		{
			x = -(levelWidth - 1);
			y -= 2;
		}
	}

	
}

void Tilemap::RegisterCollisionableTiles(int _tileId, bool _isStatic)
{
	collisionableTileMapsIds->push_back(_tileId);

	for (int i = 0; i < tiles->size(); i++)
	{
		for (int j = 0; j < collisionableTileMapsIds->size(); j++)
		{
			if (tiles->at(i)->GetTileId() == collisionableTileMapsIds->at(j))
			{
				tiles->at(i)->SetCollider(tiles->at(i)->GetTranslation(),2.0f, 2.0f,Layers::tiles, _isStatic);
				CollisionManager::GetInstance()->AddCollisionEntity(tiles->at(i), Layers::tiles);
			}
		}
	}
}