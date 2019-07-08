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
	terrain = new vector<GroundChunk*>();
	cannons = new vector<Cannon*>();
	bullets = new vector<Bullet*>();
	ship = new Ship(renderer, gameWorld, vec2(-8.0f, 7.0f), vec2(0.4f, 0.4f), 100.0f, 5.0f, 80.0f, 50.0f);

	GenerateTerrain();


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
	UpdatePhisics();
	renderer->CameraFollow(vec3(0.0f, ship->GetSprite()->GetTranslation().y ,0.0f));

	for (int i = 0; i < cannons->size(); i++)
	{
		cannons->at(i)->Update();
		if (rand()%100 ==9)
		{
			bullets->push_back(cannons->at(i)->Shoot((vec2)ship->GetSprite()->GetTranslation()));

		}
	}
	for (int i = 0; i < bullets->size(); i++) 
	{
		bullets->at(i)->Update();

	}

	if (ImputManager::GetInstance()->GetKeyDown(Escape))
	{
		return false;
	}
	ship->Update();

	return true;
}

void Game::OnDraw()
{
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
		int r = rand() % 200;
		if (r == 199 && !landPlatformGenerated)
		{
			groundChunk = new GroundChunk(renderer, gameWorld, lastPositionGenerated + (LAND_PLATFORM_SIZE + lastChunkSize), LAND_PLATFORM_SIZE, true);
			lastChunkSize = vec2(LAND_PLATFORM_SIZE.x, 0.0f);
			landPlatformGenerated = true;
		}
		else if (r % 2 == 0)
		{
			groundChunk = new GroundChunk(renderer, gameWorld, lastPositionGenerated + (GROUND_CHUNK_SIZE + lastChunkSize), GROUND_CHUNK_SIZE, false);
			lastChunkSize = vec2(GROUND_CHUNK_SIZE.x, 0.0f);
			if (rand()% 1000 == 0)
			{
				cannons->push_back(new Cannon(renderer, gameWorld, lastPositionGenerated + (GROUND_CHUNK_SIZE + lastChunkSize) + vec2(0.0f,4.0f), vec2(0.5f, 2.0f)));
				cannonGenerated = true;
			}
		}
		else
		{
			groundChunk = new GroundChunk(renderer, gameWorld, lastPositionGenerated + ((GROUND_CHUNK_SIZE + lastChunkSize) * VEC2_MINUS_Y), GROUND_CHUNK_SIZE, false);
			lastChunkSize = vec2(GROUND_CHUNK_SIZE.x, 0.0f);
			if (rand() % 1000 == 0)
			{
				cannons->push_back(new Cannon(renderer, gameWorld, lastPositionGenerated + (GROUND_CHUNK_SIZE + lastChunkSize) + vec2(0.0f, 4.0f), vec2(0.5f, 2.0f)));
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
		terrain->clear();
		GenerateTerrain();
	}

}

void Game::UpdatePhisics() 
{
	gameWorld->Step(Time::dt, 8, 8);
	gameWorld->ClearForces();
}
