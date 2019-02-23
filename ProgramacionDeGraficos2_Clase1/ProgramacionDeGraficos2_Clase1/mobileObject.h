#pragma once
#include "../EngineDLL/Material.h"
#include "../EngineDLL/Sprite.h"
#include "../EngineDll/Definitions.h"
#include "../EngineDll/CollisionManager.h"
#include "../EngineDll/Tilemap.h"
#include "../EngineDll/ImputManager.h"
#include "../EngineDll/Time.h"
class MobileObject
{
private:
	Sprite * mobileObjectSprite;
	Material * mobileObjectMaterial;
	Tilemap * tilemapToCollide;
	unsigned int textureBuffer;
	float widht;
	float height;
public:
	MobileObject(Renderer * _renderer, const char * _filename, float _animation, float _positionX, float _positionY, float _positionZ, float _height, float _widht, Tilemap * _tilemapToCollide);
	~MobileObject();
	void SetCollider(float _positionX, float _positionY, float _positionZ, float _height, float _widht);
	void Draw();
	void Update();
	Sprite * GetSprite();
	void CheckTileMapCollision(float _playerSpeed);
};

