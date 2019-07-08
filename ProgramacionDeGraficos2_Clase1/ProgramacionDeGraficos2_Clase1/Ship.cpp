#include "Ship.h"


Ship* Ship::instance = 0;

Ship* Ship::GetInstance()
{
	
	return instance;
}


Ship::Ship(Renderer * _renderer, b2World * _world, vec2 _position, vec2 _scale, float _fuel, float _upSpeed, float _rotationSpeed, float _initialForce, int _collisionLayer) : CollisionData(_collisionLayer)
{

	sprite = new Sprite(_renderer, 1.0f);
	material = new Material();
	material->LoadShaders("texturevertexshader.txt", "texturefragmentshader.txt");
	sprite->SetMaterial(material);
	sprite->SetTextureBufferId(sprite->LoadTexture("rock.bmp"));


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
	world = _world;
	b2PolygonShape shape;
	shape.SetAsBox(scale.x , scale.y );
	fixtureDef.shape = &shape;
	fixtureDef.friction = 0.3f;
	fixtureDef.density = 1.0f;
	fixtureDef.restitution = 0.0f;
	fixtureDef.filter.categoryBits = 0x0002;

	fixture = body->CreateFixture(&fixtureDef);
	body->SetTransform(body->GetPosition(), body->GetAngle() - ((90.0f * 3.1416f)/180.0f));

	body->SetUserData((void *)this);

	fixture->SetUserData((void *)this);
}


Ship::~Ship()
{
	world->DestroyBody(body);

	delete sprite;
	delete material;
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
		body->SetTransform(body->GetPosition(), body->GetAngle() + (((rotationSpeed * 3.14) / 180.0f)) * Time::dt);
	}

	if (ImputManager::GetInstance()->GetKeyDown(RightKey))
	{
		body->SetTransform(body->GetPosition(), body->GetAngle() - (((rotationSpeed * 3.14) / 180.0f)) * Time::dt);
	}

	if (ImputManager::GetInstance()->GetKeyDown(UpKey) && fuel > 0.0f)
	{
		b2Vec2 forceDirection = body->GetWorldVector(b2Vec2(0, 1));
		fuel -= Time::dt;
		body->ApplyLinearImpulse((upSpeed * Time::dt * forceDirection), body->GetPosition(), true);
	}

	if (fuel > 0)
	{
		cout << "Fuel: " << (int)fuel << "," << (int)((fuel - (int)fuel) * 100) << endl;
	}
	else
	{
		cout << "Fuel empty" << endl;
	}
}
