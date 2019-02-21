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
	static Tilemap* instance;
	int mapWidth;
	int mapHeight;
	int cantUVvertex;
	float cantX;
	float cantY;
	vector<int>* mapIds;
	vector<vector<int>> indexes;
	vector<float> vertexArrayPos;
	vector<vector<int>> bidimensionalIDs;
	vector<int> tilesWithCollides;
public:
	Tilemap(Renderer* rend, float width, float height, const char* filename, float cantTilesX, float cantTilesY);
	~Tilemap();
	static Tilemap* GetInstance();
	void Draw() override;
	void DrawMesh(int _drawType);
	void SetTextures(float* vertex, int cant);
	void LoadTexture(const char* name);
	void LoadUVs();
	void LoadMapIDs(const char* file);
	void SetTilemapVertex(float* vertex, int cant);
	void UpdateTilemap();
	void SetColliderTiles(vector<int> v);
	bool NextTileIsCollider(float x, float y);
	float GetTileX(float x);
	float GetTileY(float y);
};

