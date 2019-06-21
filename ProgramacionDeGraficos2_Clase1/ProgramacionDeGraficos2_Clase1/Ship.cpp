#include "Ship.h"



Ship::Ship(Renderer * _renderer, b2World * _world)
{

	sprite = new Sprite(_renderer, 1.0f);
	material = new Material();
	material->LoadShaders("colorvertexshader.txt", "colorfragmentshader.txt");
	sprite->SetMaterial(material);

	sprite->SetTranslation(0.0f, 5.0f, 0.0f);
	sprite->SetScale(1, 1, 0);

	bodyDef.type = b2BodyType::b2_dynamicBody;
	bodyDef.position = b2Vec2(0.0f, 5.0f);
	body = _world->CreateBody(&bodyDef);

	b2PolygonShape shape;
	shape.SetAsBox(1.0f, 1.0f);
	fixtureDef.shape = &shape;
	fixture = body->CreateFixture(&fixtureDef);

	sprite->Update();

}


Ship::~Ship()
{
}

void Ship::Draw()
{
	sprite->SetTranslation(body->GetPosition().x, body->GetPosition().y,0.0f);
	sprite->Draw();
}
