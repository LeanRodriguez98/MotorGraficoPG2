#include "Ship.h"



Ship::Ship(Renderer * _renderer, b2World * _world, vec2 _position, vec2 _scale, float _fuel, float _upSpeed, float _rotationSpeed, float _initialForce)
{

	sprite = new Sprite(_renderer, 1.0f);
	material = new Material();
	material->LoadShaders("texturevertexshader.txt", "texturefragmentshader.txt");
	sprite->SetMaterial(material);
	unsigned int textureBuffer = sprite->LoadTexture("rock.bmp");
	sprite->SetTextureBufferId(textureBuffer);


	position = _position;
	scale = _scale;
	sprite->SetTranslation(position.x, position.y, 0.0f);
	sprite->SetScale(scale.x, scale.y, 0);

	fuel = _fuel;
	upSpeed = _upSpeed;
	rotationSpeed = _rotationSpeed;
	initialForce = _initialForce;

	bodyDef.type = b2BodyType::b2_dynamicBody;
	bodyDef.position = b2Vec2(position.x, position.y);
	body = _world->CreateBody(&bodyDef);

	b2PolygonShape shape;
	shape.SetAsBox(scale.x , scale.y );
	fixtureDef.shape = &shape;
	fixtureDef.friction = 0.3f;
	fixtureDef.density = 1.0f;
	fixtureDef.restitution = 0.0f;
	fixture = body->CreateFixture(&fixtureDef);
	body->SetTransform(body->GetPosition(), body->GetAngle() - ((90.0f * 3.1416f)/180.0f));
}


Ship::~Ship()
{
}

void Ship::Draw()
{
	sprite->SetTranslation(body->GetPosition().x, body->GetPosition().y, 0.0f);
	sprite->SetRotationZ(body->GetAngle());
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

	if (!firstDraw)
	{
		sprite->Update();
		body->ApplyForce(b2Vec2(body->GetPosition().x + initialForce, body->GetPosition().y), body->GetPosition(), false);

		firstDraw = true;
	}

	if (ImputManager::GetInstance()->GetKeyDown(LeftKey))
	{
		body->SetTransform(body->GetPosition(), body->GetAngle() + (((rotationSpeed * 3.14)/180.0f)) * Time::dt);
	}

	if (ImputManager::GetInstance()->GetKeyDown(RightKey))
	{
		body->SetTransform(body->GetPosition(), body->GetAngle() - (((rotationSpeed * 3.14) / 180.0f)) * Time::dt);
	}

	if (ImputManager::GetInstance()->GetKeyDown(UpKey))
	{
		b2Vec2 forceDirection = body->GetWorldVector(b2Vec2(0, 1));
		body->ApplyLinearImpulse((upSpeed * Time::dt * forceDirection), body->GetPosition(), true);
	}

}
