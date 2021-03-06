#pragma once
#include "../EngineDLL/Include/Material.h"
#include "../EngineDLL/Include/Sprite.h"
#include "../EngineDll/Include/Definitions.h"
#include "../EngineDll/Include/CollisionManager.h"
class StaticObject
{
private:
	Sprite * staticObjectSprite;
	Material * staticObjectMaterial;
	unsigned int textureBuffer;
public:
	StaticObject(Renderer * _renderer, const char * _filename, float _animation, float _positionX, float _positionY, float _positionZ);
	~StaticObject();
	void SetCollider(float _positionX, float _positionY, float _positionZ, float _height, float _widht);
	void Draw();
	void Update();
	Sprite * GetSprite();
};

