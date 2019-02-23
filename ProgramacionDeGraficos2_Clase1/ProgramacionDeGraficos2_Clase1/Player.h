#pragma once
#include "../EngineDLL/Material.h"
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
	float height;
	float widht;

	unsigned int animationRightBuffer;
	unsigned int animationLeftBuffer;
	unsigned int animationUpBuffer;
	unsigned int animationDownBuffer;

	bool firstDraw;
public:

	Player(Renderer * _renderer, float _animation, float _speed, float _height, float _widht, float _positionX, float _positionY, float _positionZ, Tilemap * _tilemapToCollide);
	~Player();
	void Update();
	void Movement();
	void SetCollisionEntity(Layers _layer);
	void Draw();
	float GetHeight();
	float GetWidht();
	Sprite* GetSprite();
};

