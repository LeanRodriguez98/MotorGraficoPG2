#pragma once
#include "../EngineDLL/Material.h"
#include "../EngineDLL/Sprite.h"
#include "../EngineDll/Definitions.h"
#include "../EngineDll/ImputManager.h"
#include "../EngineDll/Time.h"
#include "../EngineDll//Square.h"
#include <Box2D/Box2D.h>
class GroundChunk
{
private:
	Square * sprite;
	Material * material;
	float height;
	float widht;

	b2Body * body;
	b2BodyDef bodyDef;
	b2Fixture * fixture;
	b2FixtureDef fixtureDef;

	vec2 position;
	vec2 scale;

	bool canLand;
	b2World * b2Wolrd;
public:


	GroundChunk(Renderer * _renderer, b2World * _world, vec2 _position, vec2 _scale, bool _canLand);
	~GroundChunk();
	void Draw();
	vec2 GetPosition();
	vec2 GetScale();
};

