#include "GroundChunk.h"

GroundChunk::GroundChunk(Renderer * _renderer, b2World * _world, vec2 _position, vec2 _scale, int _collisionLayer) : CollisionData(_collisionLayer)
{

	sprite = new Square(_renderer);
	material = new Material();
	material->LoadShaders("colorvertexshader.txt", "colorfragmentshader.txt");
	sprite->SetMaterial(material);
	position = _position;
	scale = _scale;
	sprite->SetTranslation(position.x, position.y, 0.0f);
	sprite->SetScale(scale.x, scale.y, 0);
	bodyDef.type = b2BodyType::b2_staticBody;
	bodyDef.position = b2Vec2(position.x, position.y);
	body = _world->CreateBody(&bodyDef);

	b2PolygonShape shape;
	shape.SetAsBox(scale.x, scale.y);
	fixtureDef.shape = &shape;
	fixtureDef.friction = 0.3f;
	fixtureDef.density = 1.0f;
	fixtureDef.restitution = 0.0f;
	fixtureDef.filter.categoryBits = 0x0008;
	fixture = body->CreateFixture(&fixtureDef);
	b2Wolrd = _world;

	body->SetUserData((void *)this);

	fixture->SetUserData((void *)this);
}


GroundChunk::~GroundChunk()
{
	b2Wolrd->DestroyBody(body);

	delete sprite;
	delete material;
}

void GroundChunk::Draw()
{
	sprite->Draw();
}

vec2 GroundChunk::GetPosition() 
{
	return position;
}

vec2 GroundChunk::GetScale()
{
	return scale;
}