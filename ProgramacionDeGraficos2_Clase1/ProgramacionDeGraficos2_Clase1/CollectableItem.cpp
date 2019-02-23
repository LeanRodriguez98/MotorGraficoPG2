#include "CollectableItem.h"



CollectableItem::CollectableItem(Renderer * _renderer,const char * _filename, float _animation, float _positionX, float _positionY, float _positionZ, float _height, float _widht)
{
	collectableItemSprite = new Sprite(_renderer, _animation);
	collectableItemMaterial = new Material();
	collectableItemMaterial->LoadShaders("texturevertexshader.txt", "texturefragmentshader.txt");
	collectableItemSprite->SetMaterial(collectableItemMaterial);

	collectableItemSprite->SetTranslation(_positionX, _positionY, _positionZ);

	height = _height;
	widht = _widht;

	textureBuffer = collectableItemSprite->LoadTexture(_filename);
	collectableItemSprite->SetTextureBufferId(textureBuffer);

}


CollectableItem::~CollectableItem()
{
	delete collectableItemSprite;
	delete collectableItemMaterial;
}


void CollectableItem::Draw() 
{
	collectableItemSprite->Draw();
}
bool CollectableItem::CheckCollision(float _playerTranslationX, float _playerTranslationY, float _playerHeight, float _playerWidht)
{
	collectableItemSprite->Update();

	if (((_playerTranslationX + (_playerWidht / 2)) >= (collectableItemSprite->GetTranslationX() - (widht / 2))) && ((_playerTranslationX - (_playerWidht / 2)) <= (collectableItemSprite->GetTranslationX() + (widht / 2))) && (_playerTranslationY + (_playerHeight / 2) >= (collectableItemSprite->GetTranslationY() - (height / 2))) && (_playerTranslationY - (_playerHeight / 2) <= (collectableItemSprite->GetTranslationY() + (height / 2))))
	{
		return true;
	}
	return false;
}

