#pragma once
#include "Shape.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

class ENGINEDLL_API Tilemap : public Shape
{
private:
	int tilemapWidth;
	int tilemapHeight;
	int cantUVvertex;
	float cantTilesX;
	float cantTilesY;
	float tileOffset;
	float tileSize;
	vector<int>* mapIds;
	vector<float> vertexArrayPos;
	vector<vector<int>> bidimensionalIDs;
	vector<int>* tilesWithCollides;
	struct TileColliderData 
	{
		float positionX;
		float width;
		float positionY;
		float height;
	};

	vector<TileColliderData>* tilesColliderData;
public:
	Tilemap(Renderer* _renderer, float _tilemapWidth, float _tilemapHeight, const char* _filename, float _cantTilesX, float _cantTilesY,float _tileOffset, float _tileSize , vector<int>* _colliderTiles);
	~Tilemap();
	void Draw() override;
	void DrawMesh(int _drawType);
	void SetTextures(float* vertex, int cant);
	void LoadTexture(const char* name);
	void LoadUVs();
	void LoadMapIDs(const char* file);
	void SetTilemapVertex(float* vertex, int cant);

	bool NextTileIsCollider(float _playerTranslationX, float _playerTranslationY, float _playerHight, float _playerWidht);


};

