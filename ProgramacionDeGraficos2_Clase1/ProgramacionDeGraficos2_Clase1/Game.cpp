#include "Game.h"

Game::Game()
{
}
Game::~Game()
{
}
bool Game::OnStart() {
	materialTilemap1 = new Material();
	unsigned int programID = materialTilemap1->LoadShaders("texturevertexshader.txt", "texturefragmentshader.txt");
	vector<int> * colliderTiles = new vector<int>();
	colliderTiles->push_back(3);
	colliderTiles->push_back(4);
	colliderTiles->push_back(5);
	colliderTiles->push_back(6);
	colliderTiles->push_back(10);
	colliderTiles->push_back(13);
	colliderTiles->push_back(14);
	colliderTiles->push_back(15);
	colliderTiles->push_back(16);
	colliderTiles->push_back(17);
	tilemap1 = new Tilemap(renderer, 40, 40, "TileMapFinal.csv", 10.0f, 7.0f, 10.0f, 2.0f, colliderTiles);
	tilemap1->SetMaterial(materialTilemap1);
	tilemap1->LoadTexture("TileMap.bmp");
	
	ImputManager::GetInstance()->SetWindow(window);

	player1 = new Player(renderer,9,2,0,0,0,tilemap1);
	player1->SetCollisionEntity(player);
	return true;
}
bool Game::OnStop() {

	delete materialTilemap1;
	delete tilemap1;
	delete player1;
	return false;
}
bool Game::OnUpdate() {

	player1->Update();
	renderer->CameraFollow(player1->GetSprite()->GetTranslation());

	CollisionManager::GetInstance()->CollisionDetector();
	
	return true;
}

void Game::OnDraw()
{

	tilemap1->Draw();
	player1->Draw();
}

