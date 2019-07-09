#pragma once
#include "../EngineDLL/Material.h"
#include "../EngineDLL/Sprite.h"
#include "../EngineDll/Definitions.h"
#include "../EngineDll/ImputManager.h"
#include "../EngineDll/Time.h"
#include <Box2D/Box2D.h>
#include "CollisionData.h"
class DeadLimit : public CollisionData
{
private:
	b2Body * body;
	b2BodyDef bodyDef;
	b2Fixture * fixture;
	b2FixtureDef fixtureDef;

	b2World * world;
	vec2 position;
	vec2 scale;
public:
	DeadLimit( b2World * _world, vec2 _position, vec2 _scale, int _collisionLayer);
	~DeadLimit();
	void UpdatePosition(vec2 position);
};

