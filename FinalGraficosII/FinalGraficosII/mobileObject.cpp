#include "mobileObject.h"



MobileObject::MobileObject(Renderer * _renderer, const char * _filename, float _animation, float _positionX, float _positionY, float _positionZ,float _height, float _widht, Tilemap * _tilemapToCollide)
{
	mobileObjectSprite = new Sprite(_renderer, _animation);
	mobileObjectMaterial = new Material();
	mobileObjectMaterial->LoadShaders("texturevertexshader.txt", "texturefragmentshader.txt");
	mobileObjectSprite->SetMaterial(mobileObjectMaterial);

	mobileObjectSprite->SetTranslation(_positionX, _positionY, _positionZ);

	textureBuffer = mobileObjectSprite->LoadTexture(_filename);
	mobileObjectSprite->SetTextureBufferId(textureBuffer);

	height = _height;
	widht = _widht;

	tilemapToCollide = _tilemapToCollide;
}


MobileObject::~MobileObject()
{
	delete mobileObjectSprite;
	delete mobileObjectMaterial;
}


void MobileObject::SetCollider(float _positionX, float _positionY, float _positionZ, float _height, float _widht)
{
	mobileObjectSprite->SetCollider(vec3(_positionX, _positionY, _positionZ), _height, _widht, not_walkeable, false);
}

void MobileObject::Draw()
{
	mobileObjectSprite->Draw();
}
void MobileObject::Update()
{
	mobileObjectSprite->Update();
}

Sprite* MobileObject::GetSprite()
{
	return mobileObjectSprite;
}

void MobileObject::CheckTileMapCollision(float _playerSpeed) 
{
	if (tilemapToCollide->NextTileIsCollider(mobileObjectSprite->GetTranslationX(), mobileObjectSprite->GetTranslationY(), height, widht))
	{
		if (ImputManager::GetInstance()->GetKeyDown(RightKey))
		{
			mobileObjectSprite->SetTranslationX(mobileObjectSprite->GetTranslationX() - (Time::dt * _playerSpeed));
		}
		else if (ImputManager::GetInstance()->GetKeyDown(LeftKey))
		{
			mobileObjectSprite->SetTranslationX(mobileObjectSprite->GetTranslationX() + (Time::dt * _playerSpeed));
		}
		else if (ImputManager::GetInstance()->GetKeyDown(UpKey))
		{
			mobileObjectSprite->SetTranslationY(mobileObjectSprite->GetTranslationY() - (Time::dt * _playerSpeed));
		}
		else if (ImputManager::GetInstance()->GetKeyDown(DownKey))
		{
			mobileObjectSprite->SetTranslationY(mobileObjectSprite->GetTranslationY() + (Time::dt * _playerSpeed));
		}
	}
}

