#pragma once
#include "../EngineDLL/Material.h"
#include "../EngineDLL/Sprite.h"
#include "../EngineDll/Definitions.h"
#include "../EngineDll/Time.h"
#include <Box2D/Box2D.h>
#include "Ship.h"
#include "Bullet.h"
#include "CollisionData.h"
class Cannon : public CollisionData
{
private:
	Sprite * sprite;
	Material * material;
	float height;
	float widht;

	b2Body * body;
	b2BodyDef bodyDef;
	b2Fixture * fixture;
	b2FixtureDef fixtureDef;
	Renderer * renderer;
	b2World * world;
	vec2 position;
	vec2 scale;

	bool firstDraw = false;
	float lastPositionY;

public:
	Cannon(Renderer * _renderer, b2World * _world, vec2 _position, vec2 _scale, int _collisionLayer);
	~Cannon();
	void Draw();
	void Update();
	Bullet* Shoot(vec2 _target);
};

