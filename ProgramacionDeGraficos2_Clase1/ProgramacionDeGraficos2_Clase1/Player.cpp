#include "Player.h"



Player::Player(Renderer * _renderer,float _animation, float _speed, float _positionX, float _positionY, float _positionZ, Tilemap * _tilemapToCollide)
{
	playerSprite = new Sprite(_renderer, _animation);
	playerMaterial = new Material();
	playerMaterial->LoadShaders("texturevertexshader.txt", "texturefragmentshader.txt");
	playerSprite->SetMaterial(playerMaterial);

	playerSprite->SetCollider(vec3(0, 0, 0), 1, 1, player, false);
	playerSprite->SetTranslation(_positionX, _positionY, _positionZ);
	speed = _speed;
	tilemapToCollide = _tilemapToCollide;

	animationRightBuffer = playerSprite->LoadTexture("SpriteSheetRight.bmp");
	animationLeftBuffer = playerSprite->LoadTexture("SpriteSheetLeft.bmp");
	animationUpBuffer = playerSprite->LoadTexture("SpriteSheetUp.bmp");
	animationDownBuffer = playerSprite->LoadTexture("SpriteSheetDown.bmp");

	playerSprite->SetTextureBufferId(animationDownBuffer);
	firstDraw = false;
}

void Player::SetCollisionEntity(Layers _layer)
{
	CollisionManager::GetInstance()->AddCollisionEntity(playerSprite, _layer);
}

Player::~Player()
{
	delete playerSprite;
	delete playerMaterial;
}

void Player::Update() 
{
	if (!firstDraw)
	{
		playerSprite->Update();
		firstDraw = true;
	}
	Movement();
}

void Player::Movement() 
{

	if (ImputManager::GetInstance()->GetKeyDown(Space))
	{
	}

	if (ImputManager::GetInstance()->GetKeyDown(RightKey))
	{
		playerSprite->SetTextureBufferId(animationRightBuffer);
		playerSprite->SetTranslationX(playerSprite->GetTranslationX() + (Time::dt * speed));
		if (tilemapToCollide->NextTileIsCollider(playerSprite->GetTranslationX(), playerSprite->GetTranslationY(), 1.6f, 1.0f))
		{
			playerSprite->SetTranslationX(playerSprite->GetTranslationX() - (Time::dt * speed));
		}
		playerSprite->Update();
	}
	else if (ImputManager::GetInstance()->GetKeyDown(LeftKey))
	{
		playerSprite->SetTextureBufferId(animationLeftBuffer);
		playerSprite->SetTranslationX(playerSprite->GetTranslationX() - (Time::dt * speed));
		if (tilemapToCollide->NextTileIsCollider(playerSprite->GetTranslationX(), playerSprite->GetTranslationY(), 1.6f, 1.0f))
		{
			playerSprite->SetTranslationX(playerSprite->GetTranslationX() + (Time::dt * speed));
		}
		playerSprite->Update();
	}
	else if (ImputManager::GetInstance()->GetKeyDown(UpKey))
	{
		playerSprite->SetTextureBufferId(animationUpBuffer);
		playerSprite->SetTranslationY(playerSprite->GetTranslationY() + (Time::dt * speed));
		if (tilemapToCollide->NextTileIsCollider(playerSprite->GetTranslationX(),playerSprite->GetTranslationY(),1.6f,1.0f))
		{
			playerSprite->SetTranslationY(playerSprite->GetTranslationY() - (Time::dt * speed));
		}
		playerSprite->Update();
	}
	else if (ImputManager::GetInstance()->GetKeyDown(DownKey))
	{
		playerSprite->SetTextureBufferId(animationDownBuffer);
		playerSprite->SetTranslationY(playerSprite->GetTranslationY() - (Time::dt * speed));
		if (tilemapToCollide->NextTileIsCollider(playerSprite->GetTranslationX(), playerSprite->GetTranslationY(), 1.6f,1.0f))
		{
			playerSprite->SetTranslationY(playerSprite->GetTranslationY() + (Time::dt * speed));
		}
		playerSprite->Update();
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
