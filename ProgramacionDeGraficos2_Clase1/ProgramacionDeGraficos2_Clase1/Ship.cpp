#include "Ship.h"



Ship::Ship(Renderer * _renderer, b2World * _world, vec2 _position, vec2 _scale)
{

	sprite = new Sprite(_renderer, 1.0f);
	material = new Material();
	material->LoadShaders("colorvertexshader.txt", "colorfragmentshader.txt");
	sprite->SetMaterial(material);
	position = _position;
	scale = _scale;
	sprite->SetTranslation(position.x, position.y, 0.0f);
	sprite->SetScale(scale.x, scale.y, 0);

	bodyDef.type = b2BodyType::b2_dynamicBody;
	bodyDef.position = b2Vec2(position.x, position.y);
	body = _world->CreateBody(&bodyDef);

	b2PolygonShape shape;
	shape.SetAsBox(scale.x , scale.y );
	fixtureDef.shape = &shape;
	fixtureDef.restitution = 0.0f;
	fixture = body->CreateFixture(&fixtureDef);

	sprite->Update();

}


Ship::~Ship()
{
}

void Ship::Draw()
{
	sprite->SetTranslation(body->GetPosition().x, body->GetPosition().y, 0.0f);
	sprite->Draw();
}

vec2 Ship::GetPosition()
{
	return position;
}

vec2 Ship::GetScale()
{
	return scale;
}

Sprite* Ship::GetSprite()
{
	return sprite;
}

void Ship::Update() 
{

}
