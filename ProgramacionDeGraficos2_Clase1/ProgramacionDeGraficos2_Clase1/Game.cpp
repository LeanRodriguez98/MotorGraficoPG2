#include "Game.h"

Game::Game()
{
	i = 0;
}
Game::~Game()
{
}
bool Game::OnStart() {
	material1 = new Material();
	unsigned int programID = material1->LoadShaders("texturevertexshader.txt", "texturefragmentshader.txt");
	
	material2 = new Material();
	unsigned int programID2 = material2->LoadShaders("texturevertexshader.txt", "texturefragmentshader.txt");
	material3 = new Material();
	unsigned int programID3 = material3->LoadShaders("texturevertexshader.txt", "texturefragmentshader.txt");

	material4 = new Material();
	unsigned int programID4 = material4->LoadShaders("VertexShader.txt", "FragmentShader.txt");

	material5 = new Material();
	unsigned int programID5 = material5->LoadShaders("ColorVertexShader.txt", "ColorFragmentShader.txt");
	
	triangle1 = new Triangle(renderer);
	triangle1->SetMaterial(material4);
	
	square1 = new Square(renderer);
	square1->SetMaterial(material5);

	circle1 = new Circle(renderer, 1, 200);
	circle1->SetMaterial(material5);

	sprite1 = new Sprite(renderer,9);
	sprite1->SetMaterial(material1);
	sprite1->LoadTexture("SpriteSheet.bmp");
	sprite1->SetCollider(vec3(0,0,0), 1, 1, player, false);
	sprite1->SetTranslationX(-5);
	
	sprite2 = new Sprite(renderer, 1);
	sprite2->SetMaterial(material2);
	sprite2->LoadTexture("bmp.bmp");
	sprite2->SetCollider(vec3(0, 0, 0),2,2, enemy, false);
	sprite2->SetTranslationX(-2);

	sprite3 = new Sprite(renderer, 1);
	sprite3->SetMaterial(material3);
	sprite3->LoadTexture("bmp.bmp");
	sprite3->SetCollider(vec3(0, 0, 0), 2, 2, walkeable, false);
	sprite3->SetTranslation(1.6F,4.5f,0);

	triangle1->SetTranslation(6, 5, 0);
	square1->SetTranslation(-1, 5, 0);
	circle1->SetTranslation(-5, 5, 0);

	CollisionManager::GetInstance()->AddCollisionEntity(sprite1, player);
	CollisionManager::GetInstance()->AddCollisionEntity(sprite2, enemy);
	CollisionManager::GetInstance()->AddCollisionEntity(sprite3, walkeable);

	
	
	return true;
}
bool Game::OnStop() {

	delete material1;
	delete material2;
	delete material3;
	delete material4;
	delete material5;
	delete triangle1;
	delete square1;
	delete circle1;
	delete sprite1;
	delete sprite2;
	delete sprite3;
	
	return false;
}
bool Game::OnUpdate() {
	i++;
	triangle1->SetRotation(0.0f, 0.0f, triangle1->GetRotationZ() + Time::dt);
	
	if (circle1->GetScaleX() < 3)
	{
		circle1->SetScale(circle1->GetScaleX() + Time::dt, circle1->GetScaleY() + Time::dt, 0.0f);
	}
	
	sprite1->Update();
	sprite1->SetTranslationX(sprite1->GetTranslationX() + Time::dt);
	
	sprite2->Update();

	sprite3->Update();
	sprite3->SetTranslationY(sprite3->GetTranslationY() - Time::dt);
	CollisionManager::GetInstance()->CollisionDetector();
	
	return true;
}

void Game::OnDraw()
{
	triangle1->Draw();
	square1->Draw();
	circle1->Draw();
	
	sprite1->Draw();
	
	sprite2->Draw();
	sprite3->Draw();
}

