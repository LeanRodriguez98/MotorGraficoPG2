#include "Game.h"
#include <ctime>
Game::Game()
{
}
Game::~Game()
{
}
bool Game::OnStart() {
	
	srand(time(0));
	
	ImputManager::GetInstance()->SetWindow(window);
	gameWorld = new b2World(b2Vec2(0.0f, -1.62));
	gameWorld->SetContactListener(&collisionListener);
	terrain = new vector<GroundChunk*>();
	cannons = new vector<Cannon*>();
	bullets = new vector<Bullet*>();
	ship = new Ship(renderer, gameWorld, vec2(-8.0f, 7.0f), vec2(0.4f, 0.4f), 100.0f, 5.0f, 80.0f, 50.0f, LAYER_PLAYER);


	mainMenuMaterial = new Material();
	mainMenuMaterial->LoadShaders("texturevertexshader.txt", "texturefragmentshader.txt");
	mainMenuSprite = new Sprite(renderer, 1.0f);
	mainMenuSprite->SetMaterial(mainMenuMaterial);
	unsigned int mainMenuTextureBufferID = mainMenuSprite->LoadTexture("MainMenu.bmp");
	mainMenuSprite->SetTextureBufferId(mainMenuTextureBufferID);
	mainMenuSprite->SetScale(10.0f, 10.0f, 1.0f);

	youWinMaterial = new Material();
	youWinMaterial->LoadShaders("texturevertexshader.txt", "texturefragmentshader.txt");
	youWinSprite = new Sprite(renderer, 1.0f);
	youWinSprite->SetMaterial(youWinMaterial);
	unsigned int youWinTextureBufferID = youWinSprite->LoadTexture("YouWin.bmp");
	youWinSprite->SetTextureBufferId(youWinTextureBufferID);
	youWinSprite->SetScale(10.0f, 10.0f, 1.0f);

	gameOverMaterial = new Material();
	gameOverMaterial->LoadShaders("texturevertexshader.txt", "texturefragmentshader.txt");
	gameOverSprite = new Sprite(renderer, 1.0f);
	gameOverSprite->SetMaterial(gameOverMaterial);
	unsigned int gameOverTextureBufferID = gameOverSprite->LoadTexture("GameOver.bmp");
	gameOverSprite->SetTextureBufferId(gameOverTextureBufferID);
	gameOverSprite->SetScale(10.0f, 10.0f, 1.0f);

	GenerateTerrain();

	gameState = GameStates::mainMenu;

	leftLimit = new DeadLimit(gameWorld, vec2(-11.5f, 0.0f), vec2(0.5f, 10.0f), LAYER_DEAD_LIMIT);
	rightLimit = new DeadLimit(gameWorld, vec2(11.5f,0.0f),vec2(0.5f,10.0f), LAYER_DEAD_LIMIT);

	return true;
}
bool Game::OnStop() {

	delete ship;
	for (int i = 0; i < terrain->size(); i++)
	{
		delete terrain->at(i);
	}
	delete gameWorld;
	return false;
}
bool Game::OnUpdate() {
	switch (gameState)
	{
	case GameStates::mainMenu:
		renderer->CameraFollow(mainMenuSprite->GetTranslation());
		mainMenuSprite->Update();
		if (ImputManager::GetInstance()->GetKeyDown(EnterKey))
		{
			gameState = GameStates::game;
		}
		break;
	
	case GameStates::game:
		UpdatePhisics();

		renderer->CameraFollow(vec3(0.0f, ship->GetSprite()->GetTranslation().y, 0.0f));
		ship->Update();

		leftLimit->UpdatePosition(ship->GetSprite()->GetTranslation());
		rightLimit->UpdatePosition(ship->GetSprite()->GetTranslation());

		if (!ship->isAlive)
		{
			gameState = GameStates::gameOver;
		}

		if (ship->landed)
		{
			gameState = GameStates::youWin;
		}

		for (int i = 0; i < cannons->size(); i++)
		{
			cannons->at(i)->Update();
			if (rand() % 100 == 99)
			{
				bullets->push_back(cannons->at(i)->Shoot((vec2)ship->GetSprite()->GetTranslation()));
			}
		}
		for (int i = 0; i < bullets->size(); i++)
		{
			bullets->at(i)->Update();
		}

		for (int i = 0; i < bullets->size(); i++)
		{
			if (!bullets->at(i)->isAlive)
			{
				bullets->at(i)->~Bullet();
				bullets->erase(bullets->begin() + i);
				break;
			}
		}
		break;
	case GameStates::gameOver:
		renderer->CameraFollow(gameOverSprite->GetTranslation());
		gameOverSprite->Update();

		break;

	case GameStates::youWin:
		renderer->CameraFollow(youWinSprite->GetTranslation());
		youWinSprite->Update();

		break;
	default:
		break;
	}

	if (ImputManager::GetInstance()->GetKeyDown(EscapeKey))
	{
		return false;
	}

	return true;
}

void Game::OnDraw()
{
	switch (gameState)
	{
	case GameStates::mainMenu:
		mainMenuSprite->Draw();
		break;
	case GameStates::game:
		ship->Draw();

		for (int i = 0; i < terrain->size(); i++)
		{
			terrain->at(i)->Draw();
		}
		for (int i = 0; i < cannons->size(); i++)
		{
			cannons->at(i)->Draw();
		}
		for (int i = 0; i < bullets->size(); i++)
		{
			bullets->at(i)->Draw();
		}
		break;
	case GameStates::gameOver:
		gameOverSprite->Draw();
		break;
	case GameStates::youWin:
		youWinSprite->Draw();
		break;
	default:
		break;

	}
		
}


void Game::GenerateTerrain() 
{
	vec2 lastPositionGenerated = START_GENERATE_POSITION;
	vec2 lastChunkSize = vec2(GROUND_CHUNK_SIZE.x , 0.0f);
	bool landPlatformGenerated = false;
	bool cannonGenerated = false;
	for (float i = SCREEN_WIDHT; i > 0; i+=0)
	{
		GroundChunk * groundChunk;
		int r = rand() % 100;
		if (r == 99 && !landPlatformGenerated)
		{
			groundChunk = new GroundChunk(renderer, gameWorld, lastPositionGenerated + (LAND_PLATFORM_SIZE + lastChunkSize), LAND_PLATFORM_SIZE,LAYER_LAND_PLATFORM);
			lastChunkSize = vec2(LAND_PLATFORM_SIZE.x, 0.0f);
			landPlatformGenerated = true;
		}
		else if (r % 2 == 0)
		{
			groundChunk = new GroundChunk(renderer, gameWorld, lastPositionGenerated + (GROUND_CHUNK_SIZE + lastChunkSize), GROUND_CHUNK_SIZE, LAYER_GROUND);
			lastChunkSize = vec2(GROUND_CHUNK_SIZE.x, 0.0f);
			if (rand()% 1000 == 0)
			{
				cannons->push_back(new Cannon(renderer, gameWorld, lastPositionGenerated + (GROUND_CHUNK_SIZE + lastChunkSize) + vec2(0.0f,4.0f), vec2(0.5f, 2.0f),LAYER_CANNON));
				cannonGenerated = true;
			}
		}
		else
		{
			groundChunk = new GroundChunk(renderer, gameWorld, lastPositionGenerated + ((GROUND_CHUNK_SIZE + lastChunkSize) * VEC2_MINUS_Y), GROUND_CHUNK_SIZE, LAYER_GROUND);
			lastChunkSize = vec2(GROUND_CHUNK_SIZE.x, 0.0f);
			if (rand() % 1000 == 0)
			{
				cannons->push_back(new Cannon(renderer, gameWorld, lastPositionGenerated + (GROUND_CHUNK_SIZE + lastChunkSize) + vec2(0.0f, 4.0f), vec2(0.5f, 2.0f), LAYER_CANNON));
				cannonGenerated = true;
			}
		}
		i -= groundChunk->GetScale().x;
		lastPositionGenerated = groundChunk->GetPosition();
		terrain->push_back(groundChunk);
	}

	if (!landPlatformGenerated || !cannonGenerated)
	{
		for (int i = 0; i < terrain->size(); i++)
		{
			delete terrain->at(i);
		}
		for (int i = 0; i < cannons->size(); i++)
		{
			delete cannons->at(i);
		}
		terrain->clear(); 
		cannons->clear();
		GenerateTerrain();
	}

}

void Game::UpdatePhisics() 
{
	gameWorld->Step(Time::dt, 8, 8);
	gameWorld->ClearForces();
}
