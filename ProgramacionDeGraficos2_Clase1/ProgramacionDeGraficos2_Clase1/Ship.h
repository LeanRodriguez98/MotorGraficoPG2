#pragma once
#include "../EngineDLL/Material.h"
#include "../EngineDLL/Sprite.h"
#include "../EngineDll/Definitions.h"
#include "../EngineDll/ImputManager.h"
#include "../EngineDll/Time.h"
#include <Box2D/Box2D.h>
#include "CollisionData.h"
class Ship : public CollisionData
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

	b2World * world;
	vec2 position;
	vec2 scale;

	bool firstDraw = false;
	float fuel;
	float upSpeed;
	float rotationSpeed;
	float initialForce;
	float velocity;
	float auxVelocity;

public:
	Ship(Renderer * _renderer, b2World * _world, vec2 _position, vec2 _scale, float _fuel, float _upSpeed, float _rotationSpeed, float _initialForce, int _collisionLayer);
	~Ship();
	void Draw();
	void Update();
	vec2 GetPosition();
	vec2 GetScale();
	Sprite* GetSprite();
	void Land();
	bool landed = false;
};

