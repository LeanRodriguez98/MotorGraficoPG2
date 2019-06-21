#include "GroundChunk.h"



GroundChunk::GroundChunk(Renderer * _renderer, b2World * _world)
{

	sprite = new Sprite(_renderer, 1.0f);
	material = new Material();
	material->LoadShaders("colorvertexshader.txt", "colorfragmentshader.txt");
	sprite->SetMaterial(material);

	sprite->SetTranslation(0.0f, 0.0f, 0.0f);
	sprite->SetScale(1, 0.2, 0);

	bodyDef.type = b2BodyType::b2_staticBody;
	bodyDef.position = b2Vec2(0.0f, 0.0f);
	body = _world->CreateBody(&bodyDef);

	b2PolygonShape shape;
	shape.SetAsBox(0.5f, 0.1f);
	fixtureDef.shape = &shape;
	fixture = body->CreateFixture(&fixtureDef);

	sprite->Update();
}


GroundChunk::~GroundChunk()
{

}

void GroundChunk::Draw()
{
	sprite->Draw();
}
