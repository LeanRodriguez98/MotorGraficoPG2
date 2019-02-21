#include "Player.h"



Player::Player(Renderer * _renderer,float _animation, const char* filename, float _speed, float _positionX, float _positionY, float _positionZ)
{
	playerSprite = new Sprite(_renderer, _animation);
	playerMaterial = new Material();
	playerMaterial->LoadShaders("texturevertexshader.txt", "texturefragmentshader.txt");
	playerSprite->SetMaterial(playerMaterial);
	//playerSprite->LoadTexture("SpriteSheet.bmp");
	playerSprite->LoadTexture(filename);
	playerSprite->SetCollider(vec3(0, 0, 0), 1, 1, player, false);
	playerSprite->SetTranslation(_positionX, _positionY, _positionZ);
	speed = _speed;
}

void Player::SetCollisionEntity(Layers _layer)
{
	CollisionManager::GetInstance()->AddCollisionEntity(playerSprite, _layer);
}

Player::~Player()
{
}

void Player::Update() 
{
	playerSprite->Update();
	Movement();
}

void Player::Movement() 
{
	if (ImputManager::GetInstance()->GetKeyDown(RightKey))
	{
		playerSprite->SetTranslationX(playerSprite->GetTranslationX() + (Time::dt * speed));
	}
	else if (ImputManager::GetInstance()->GetKeyDown(LeftKey))
	{
		playerSprite->SetTranslationX(playerSprite->GetTranslationX() - (Time::dt * speed));
	}
	else if (ImputManager::GetInstance()->GetKeyDown(UpKey))
	{
		playerSprite->SetTranslationY(playerSprite->GetTranslationY() + (Time::dt * speed));
	}
	else if (ImputManager::GetInstance()->GetKeyDown(DownKey))
	{
		playerSprite->SetTranslationY(playerSprite->GetTranslationY() - (Time::dt * speed));
	}
}

void Player::Draw() 
{
	playerSprite->Draw();
}

Sprite* Player::GetSprite() 
{
	return playerSprite;
}
