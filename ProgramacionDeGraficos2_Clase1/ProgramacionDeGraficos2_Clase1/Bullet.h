#pragma once
#include "../EngineDLL/Material.h"
#include "../EngineDLL/Sprite.h"
#include "../EngineDll/Definitions.h"
#include "../EngineDll/ImputManager.h"
#include "../EngineDll/Time.h"
#include <Box2D/Box2D.h>
class Bullet
{
	Sprite * sprite;
	Material * material;
	float height;
	float widht;

	b2Body * body;
	b2BodyDef bodyDef;
	b2Fixture * fixture;
	b2FixtureDef fixtureDef;


	vec2 position;
	float radius;

	bool firstDraw = false;
	vec2 directionShoot;
public:
	Bullet(Renderer * _renderer, b2World * _world, vec2 _position, float _radius, vec2 _directionShoot);
	~Bullet();
	void Draw();
	void Update();
	vec2 GetPosition();
	float GetRadius();
	Sprite* GetSprite();
};

