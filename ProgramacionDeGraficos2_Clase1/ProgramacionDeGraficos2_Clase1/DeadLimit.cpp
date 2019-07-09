#include "DeadLimit.h"



DeadLimit::DeadLimit(b2World * _world, vec2 _position, vec2 _scale, int _collisionLayer) : CollisionData(_collisionLayer)
{

	position = _position;
	scale = _scale;

	bodyDef.type = b2BodyType::b2_staticBody;
	bodyDef.position = b2Vec2(position.x, position.y);
	body = _world->CreateBody(&bodyDef);
	world = _world;
	b2PolygonShape shape;
	shape.SetAsBox(scale.x, scale.y);
	fixtureDef.shape = &shape;
	fixtureDef.friction = 0.3f;
	fixtureDef.density = 1.0f;
	fixtureDef.restitution = 0.0f;
	fixtureDef.filter.categoryBits = 0x0010;

	fixture = body->CreateFixture(&fixtureDef);

	body->SetUserData((void *)this);
	fixture->SetUserData((void *)this);
}


DeadLimit::~DeadLimit()
{
}

void DeadLimit::UpdatePosition(vec2 position)
{
	body->SetTransform(b2Vec2(body->GetPosition().x, position.y), body->GetAngle());
}
