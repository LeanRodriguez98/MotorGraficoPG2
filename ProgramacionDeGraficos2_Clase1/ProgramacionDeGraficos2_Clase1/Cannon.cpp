#include "Cannon.h"


Cannon::Cannon(Renderer * _renderer, b2World * _world, vec2 _position, vec2 _scale, int _collisionLayer) : CollisionData(_collisionLayer)
{
	sprite = new Sprite(_renderer, 1.0f);
	material = new Material();
	material->LoadShaders("texturevertexshader.txt", "texturefragmentshader.txt");
	sprite->SetMaterial(material);
	sprite->SetTextureBufferId(sprite->LoadTexture("Cannon.bmp"));
	renderer = _renderer;
	position = _position;
	scale = _scale;
	sprite->SetTranslation(position.x, position.y, 0.0f);
	sprite->SetScale(scale.x, scale.y, 0);
	world = _world;
	bodyDef.type = b2BodyType::b2_dynamicBody;
	bodyDef.position = b2Vec2(position.x, position.y);
	body = _world->CreateBody(&bodyDef);

	b2PolygonShape shape;
	shape.SetAsBox(scale.x, scale.y);
	fixtureDef.shape = &shape;
	fixtureDef.friction = 0.3f;
	fixtureDef.density = 1.0f;
	fixtureDef.restitution = 0.0f;
	fixtureDef.filter.categoryBits = 0x0004;

	fixture = body->CreateFixture(&fixtureDef);

	body->SetUserData((void *)this);

	fixture->SetUserData((void *)this);
}


Cannon::~Cannon()
{
	world->DestroyBody(body);

	delete sprite;
	delete material;
}


void Cannon::Draw() 
{
	lastPositionY = body->GetPosition().y;
	body->SetTransform(b2Vec2(position.x, body->GetPosition().y), 0.0f);
	if (body->GetPosition().y < lastPositionY)
	{
		body->SetTransform(b2Vec2(position.x, lastPositionY), 0.0f);
	}

	sprite->SetTranslation(body->GetPosition().x, body->GetPosition().y, 0.0f);
	sprite->SetRotationZ(body->GetAngle());
	sprite->Draw();


}
void Cannon::Update() 
{
	if (!firstDraw)
	{
		sprite->Update();
		firstDraw = true;
	}
	

}

Bullet* Cannon::Shoot(vec2 _target) 
{
	return new Bullet(renderer, world, vec2(sprite->GetTranslation().x, sprite->GetTranslation().y), 0.2f, _target, LAYER_BULLET);
}

