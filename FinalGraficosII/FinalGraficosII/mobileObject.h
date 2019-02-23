#pragma once
#include "../EngineDLL/Include/Material.h"
#include "../EngineDLL/Include/Sprite.h"
#include "../EngineDll/Include/Definitions.h"
#include "../EngineDll/Include/CollisionManager.h"
#include "../EngineDll/Include/Tilemap.h"
#include "../EngineDll/Include/ImputManager.h"
#include "../EngineDll/Include/Time.h"
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

