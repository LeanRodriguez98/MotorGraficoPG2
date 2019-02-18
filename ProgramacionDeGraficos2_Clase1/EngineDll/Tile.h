#pragma once
#include "Shape.h"
class ENGINEDLL_API Tile : public Shape
{
private:
	int tileId;
	float tileWidht;
	float tileHeight;
	int horizontalTiles;
	int verticalTiles;
public:
	Tile(Renderer* _renderer, int _tileId, float _width, float _height);
	~Tile();
	void Draw() override;
	void SetTileTexture(float* vertex, int cant);
	void LoadTileTexture(const char* name);
	void CalculateUVTile();
	int GetTileId();
};

