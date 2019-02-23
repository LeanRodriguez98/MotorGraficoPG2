#include "StaticObject.h"



StaticObject::StaticObject(Renderer * _renderer, const char * _filename, float _animation, float _positionX, float _positionY, float _positionZ)
{
	staticObjectSprite = new Sprite(_renderer, _animation);
	staticObjectMaterial = new Material();
	staticObjectMaterial->LoadShaders("texturevertexshader.txt", "texturefragmentshader.txt");
	staticObjectSprite->SetMaterial(staticObjectMaterial);

	staticObjectSprite->SetTranslation(_positionX, _positionY, _positionZ);

	textureBuffer = staticObjectSprite->LoadTexture(_filename);
	staticObjectSprite->SetTextureBufferId(textureBuffer);
}

void StaticObject::SetCollider(float _positionX, float _positionY, float _positionZ, float _height, float _widht) 
{
	staticObjectSprite->SetCollider(vec3(_positionX, _positionY, _positionZ), _height, _widht, not_walkeable, true);
}

StaticObject::~StaticObject()
{
	delete staticObjectSprite;
	delete staticObjectMaterial;
}


void StaticObject::Draw() 
{
	staticObjectSprite->Draw();
}
void StaticObject::Update() 
{
	staticObjectSprite->Update();
}

Sprite* StaticObject::GetSprite()
{
	return staticObjectSprite;
}