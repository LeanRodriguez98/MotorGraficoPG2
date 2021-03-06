#pragma once
#include "../EngineDLL/Include/Material.h"
#include "../EngineDLL/Include/Sprite.h"
#include "../EngineDll/Include/Definitions.h"
#include "../EngineDll/Include/CollisionManager.h"
class CollectableItem
{
private:
	Sprite * collectableItemSprite;
	Material * collectableItemMaterial;
	unsigned int textureBuffer;

	float height;
	float widht;
public:
	CollectableItem(Renderer * _renderer, const char * _filename, float _animation, float _positionX, float _positionY, float _positionZ, float _height, float _widht);
	~CollectableItem();
	bool CheckCollision(float _playerTranslationX, float _playerTranslationY, float _playerHeight, float _playerWidht);
	void Draw();
};

