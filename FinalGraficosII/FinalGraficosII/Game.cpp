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

	player1 = new Player(renderer,9,PLAYER_SPEED,1.6f,1.0f,0,0,0,tilemap1);
	player1->SetCollisionEntity(player);


	bones = new vector<CollectableItem*>();
	bones->push_back(new CollectableItem(renderer, "bone.bmp", 1.0f, 4.0f, 0.0f, 0.0f, 0.5f, 1.0f));
	bones->push_back(new CollectableItem(renderer, "bone.bmp", 1.0f, 35.0f, 2.0f, 0.0f, 0.5f, 1.0f));
	bones->push_back(new CollectableItem(renderer, "bone.bmp", 1.0f, 4.0f, -20.0f, 0.0f, 0.5f, 1.0f));
	bones->push_back(new CollectableItem(renderer, "bone.bmp", 1.0f, 24.0f, -31.0f, 0.0f, 0.5f, 1.0f));
	bones->push_back(new CollectableItem(renderer, "bone.bmp", 1.0f, 34.0f, -12.0f, 0.0f, 0.5f, 1.0f));
	bones->push_back(new CollectableItem(renderer, "bone.bmp", 1.0f, 14.0f, -42.0f, 0.0f, 0.5f, 1.0f));
	bones->push_back(new CollectableItem(renderer, "bone.bmp", 1.0f, 45.0f, -62.0f, 0.0f, 0.5f, 1.0f));
	bones->push_back(new CollectableItem(renderer, "bone.bmp", 1.0f, 35.0f, -54.0f, 0.0f, 0.5f, 1.0f));
	bones->push_back(new CollectableItem(renderer, "bone.bmp", 1.0f, 2.0f, -64.0f, 0.0f, 0.5f, 1.0f));
	bones->push_back(new CollectableItem(renderer, "bone.bmp", 1.0f, 62.0f, -30.0f, 0.0f, 0.5f, 1.0f));


	trees = new vector<StaticObject*>();

	trees->push_back(new StaticObject(renderer, "Tree.bmp", 1.0f, 5.0f, -33.0f, 0.0f));
	trees->push_back(new StaticObject(renderer, "Tree.bmp", 1.0f, 5.0f, -43.0f, 0.0f));
	trees->push_back(new StaticObject(renderer, "Tree.bmp", 1.0f, 50.0f, -48.0f, 0.0f));
	trees->push_back(new StaticObject(renderer, "Tree.bmp", 1.0f, 55.0f, -33.0f, 0.0f));
	trees->push_back(new StaticObject(renderer, "Tree.bmp", 1.0f, 45.0f, -10.0f, 0.0f));
	trees->push_back(new StaticObject(renderer, "Tree.bmp", 1.0f, 65.0f, -60.0f, 0.0f));

	for (int i = 0; i < trees->size(); i++)
	{
		trees->at(i)->GetSprite()->SetScale(3.0f, 3.0f, 1.0f);
		trees->at(i)->SetCollider(0.0f, -1.0f, 0.0f, 3.0f, 2.0f);
		CollisionManager::GetInstance()->AddCollisionEntity(trees->at(i)->GetSprite(), not_walkeable);
	}


	rocks = new vector<MobileObject*>();

	rocks->push_back(new MobileObject(renderer, "Rock.bmp", 1.0f, 22.0f, 1.0f, 0.0f, 2.0f, 2.0f, tilemap1));
	rocks->push_back(new MobileObject(renderer, "Rock.bmp", 1.0f, 22.0f, -2.5f, 0.0f, 2.0f, 2.0f, tilemap1));
	rocks->push_back(new MobileObject(renderer, "Rock.bmp", 1.0f, 30.0f, -20.0f, 0.0f, 2.0f, 2.0f, tilemap1));
	rocks->push_back(new MobileObject(renderer, "Rock.bmp", 1.0f, 45.0f, -30.0f, 0.0f, 2.0f, 2.0f, tilemap1));
	rocks->push_back(new MobileObject(renderer, "Rock.bmp", 1.0f, 0.0f, -60.0f, 0.0f, 2.0f, 2.0f, tilemap1));
	rocks->push_back(new MobileObject(renderer, "Rock.bmp", 1.0f, 40.0f, -60.0f, 0.0f, 2.0f, 2.0f, tilemap1));

	for (int i = 0; i < rocks->size(); i++)
	{
		rocks->at(i)->SetCollider(0.0f, 0.0f, 0.0f, 3.0f, 2.0f);
		CollisionManager::GetInstance()->AddCollisionEntity(rocks->at(i)->GetSprite(), not_walkeable);
	}

	mainMenuMaterial = new Material();
	mainMenuMaterial->LoadShaders("texturevertexshader.txt", "texturefragmentshader.txt");
	mainMenuSprite = new Sprite(renderer,1.0f);
	mainMenuSprite->SetMaterial(mainMenuMaterial);
	unsigned int mainMenuTextureBufferID = mainMenuSprite->LoadTexture("MainMenu.bmp");
	mainMenuSprite->SetTextureBufferId(mainMenuTextureBufferID);
	mainMenuSprite->SetScale(10.0f, 10.0f, 1.0f);

	gameOverMaterial = new Material();
	gameOverMaterial->LoadShaders("texturevertexshader.txt", "texturefragmentshader.txt");
	gameOverSprite = new Sprite(renderer, 1.0f);
	gameOverSprite->SetMaterial(gameOverMaterial);
	unsigned int gameOverTextureBufferID = gameOverSprite->LoadTexture("GameOver.bmp");
	gameOverSprite->SetTextureBufferId(gameOverTextureBufferID);
	gameOverSprite->SetScale(10.0f, 10.0f, 1.0f);


	gamestate = GameState::MainMenu;

	return true;
}
bool Game::OnStop() {

	delete bones;
	delete trees;
	delete rocks;
	delete materialTilemap1;
	delete tilemap1;
	delete player1;
	return false;
}
bool Game::OnUpdate() {


	if (ImputManager::GetInstance()->GetKeyDown(Escape))
	{
		return false;
	}

	if (gamestate == GameState::MainMenu)
	{
		mainMenuSprite->Update();
		renderer->CameraFollow(mainMenuSprite->GetTranslation());

		if (ImputManager::GetInstance()->GetKeyDown(Space)) 
		{
			gamestate = GameState::InGame;
		}
	}
	else if (gamestate == GameState::InGame)
	{
		player1->Update();
		renderer->CameraFollow(player1->GetSprite()->GetTranslation());
		CollisionManager::GetInstance()->CollisionDetector();

		for (size_t i = 0; i < bones->size(); i++)
		{
			if (bones->at(i)->CheckCollision(player1->GetSprite()->GetTranslationX(), player1->GetSprite()->GetTranslationY(), player1->GetHeight(), player1->GetWidht()))
			{
				bones->at(i)->~CollectableItem();
				bones->erase(bones->begin() + i);
				break;
			}
		}

		for (int i = 0; i < trees->size(); i++)
		{
			trees->at(i)->Update();

		}

		for (int i = 0; i < rocks->size(); i++)
		{
			rocks->at(i)->Update();
			rocks->at(i)->CheckTileMapCollision(PLAYER_SPEED);
		}

		if (bones->size() == 0)
		{
			gamestate = GameState::GameOver;
		}
	}
	else if(gamestate == GameState::GameOver)
	{
		gameOverSprite->Update();
		renderer->CameraFollow(gameOverSprite->GetTranslation());

		if (ImputManager::GetInstance()->GetKeyDown(Space))
		{
			return false;
		}
	}
	return true;
}

void Game::OnDraw()
{



	if (gamestate == GameState::MainMenu)
	{
		mainMenuSprite->Draw();
	}
	else if (gamestate == GameState::InGame)
	{
		tilemap1->Draw();
		player1->Draw();
		for (int i = 0; i < bones->size(); i++)
		{
			bones->at(i)->Draw();
		}
		for (int i = 0; i < trees->size(); i++)
		{
			trees->at(i)->Draw();

		}
		for (int i = 0; i < rocks->size(); i++)
		{
			rocks->at(i)->Draw();

		}
	}
	else if (gamestate == GameState::GameOver)
	{
		gameOverSprite->Draw();
	}
}

