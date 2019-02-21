#pragma once
#include "../EngineDLL/Material.h"
#include "../EngineDLL/TextureImporter.h"
#include "../EngineDLL/Sprite.h"
#include "../EngineDll/Definitions.h"
#include "../EngineDll/CollisionManager.h"
#include "../EngineDll/Tilemap.h"
#include "../EngineDll/ImputManager.h"
#include "../EngineDll/Time.h"
class Player
{
private:
	Sprite * playerSprite;
	Material * playerMaterial;
	Tilemap * tilemapToCollide;
	float speed;
	unsigned int programID;
public:

	Player(Renderer * _renderer, float _animation, const char* filename, float _speed, float _positionX, float _positionY, float _positionZ, Tilemap * _tilemapToCollide);
	~Player();
	void Update();
	void Movement();
	void SetCollisionEntity(Layers _layer);
	void Draw();
	Sprite* GetSprite();
};

