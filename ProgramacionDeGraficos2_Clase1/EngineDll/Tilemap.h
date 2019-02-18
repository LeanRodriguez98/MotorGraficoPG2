#pragma once
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include "Tile.h"
#include "Exports.h"
#include "CollisionManager.h"
using namespace std;
class ENGINEDLL_API Tilemap
{
private:
	Renderer * renderer;
	const char* tileMap;
	vector<int>* tileMapsIds;
	vector<int>* collisionableTileMapsIds;
	vector<Tile*>* tiles;
	Material* tilesMaterial;
	float levelHeight;
	float levelWidth;
	float tileSheetTilesX;
	float tileSheetTilesY;
	const char* texture;
public:
	Tilemap(Renderer* _renderer, const char* _tileMapName, float _levelWidth, float _levelHeight, Material* _material, const char* _tilesSheetName, float _tileSheetTilesX, float _tileSheetTilesY);
	~Tilemap();
	void LoadTileMap();
	void DrawTileMap();
	void RegisterCollisionableTiles(int _tileId, bool _isStatic);
	void ChargeTiles();
};

