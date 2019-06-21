#include "GroundChunk.h"



GroundChunk::GroundChunk(Renderer * _renderer, b2World * _world, vec2 _position, vec2 _scale, bool _canLand)
{

	sprite = new Square(_renderer);
	material = new Material();
	material->LoadShaders("colorvertexshader.txt", "colorfragmentshader.txt");
	sprite->SetMaterial(material);
	position = _position;
	scale = _scale;
	sprite->SetTranslation(position.x, position.y, 0.0f);
	sprite->SetScale(scale.x, scale.y, 0);
	canLand = _canLand;
	bodyDef.type = b2BodyType::b2_staticBody;
	bodyDef.position = b2Vec2(position.x, position.y);
	body = _world->CreateBody(&bodyDef);

	b2PolygonShape shape;
	shape.SetAsBox(scale.x, scale.y);
	fixtureDef.shape = &shape;
	fixture = body->CreateFixture(&fixtureDef);

}


GroundChunk::~GroundChunk()
{

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