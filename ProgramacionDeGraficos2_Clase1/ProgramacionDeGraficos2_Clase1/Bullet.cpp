#include "Bullet.h"



Bullet::Bullet(Renderer * _renderer, b2World * _world, vec2 _position, float _radius, vec2 _directionShoot, int _collisionLayer) : CollisionData(_collisionLayer)
{

	sprite = new Sprite(_renderer, 1.0f);
	material = new Material();
	material->LoadShaders("texturevertexshader.txt", "texturefragmentshader.txt");
	sprite->SetMaterial(material);
	sprite->SetTextureBufferId(sprite->LoadTexture("rock.bmp"));


	position = _position;
	radius = _radius;
	sprite->SetTranslation(position.x, position.y, 0.0f);
	sprite->SetScale(radius, radius, 0);
	world = _world;
	directionShoot = _directionShoot;
	bodyDef.type = b2BodyType::b2_dynamicBody;
	bodyDef.position = b2Vec2(position.x, position.y);
	body = _world->CreateBody(&bodyDef);
	b2CircleShape shape;
	shape.m_radius = radius;
	fixtureDef.shape = &shape;
	fixtureDef.friction = 0.3f;
	fixtureDef.density = 1.0f;
	fixtureDef.restitution = 0.0f;
	fixtureDef.filter.categoryBits = 0x0006;
	fixtureDef.filter.maskBits = 0xFFFF & ~0x0004;
	fixture = body->CreateFixture(&fixtureDef);
	body->SetUserData((void *)this);
	
	fixture->SetUserData((void *)this);
}


Bullet::~Bullet()
{
	world->DestroyBody(body);

	delete sprite;
	delete material;
}

void Bullet::Draw()
{
	sprite->SetTranslation(body->GetPosition().x, body->GetPosition().y, 0.0f);
	sprite->SetRotationZ(body->GetAngle());
	sprite->Draw();
}

vec2 Bullet::GetPosition()
{
	return position;
}

float Bullet::GetRadius()
{
	return radius;
}

Sprite* Bullet::GetSprite()
{
	return sprite;
}

void Bullet::Update()
{

	if (!firstDraw)
	{
		sprite->Update();
		body->ApplyForce( 5.0f * (b2Vec2(directionShoot.x, directionShoot.y) - body->GetPosition()), body->GetPosition(), false);

		firstDraw = true;
	}


}
