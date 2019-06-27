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
	GenerateTerrain();

	ship = new Ship(renderer, gameWorld, vec2(-5.0f, 6.0f), vec2(0.4f,0.4f));

	return true;
}
bool Game::OnStop() {

	delete ship;
	for (int i = 0; i < terrain->size(); i++)
	{
		delete terrain->at(i);
	}
	return false;
}
bool Game::OnUpdate() {
	UpdatePhisics();
	renderer->CameraFollow(vec3(0.0f, ship->GetSprite()->GetTranslation().y ,0.0f));
	if (ImputManager::GetInstance()->GetKeyDown(Escape))
	{
		return false;
	}

	return true;
}

void Game::OnDraw()
{
	ship->Draw();
	for (int i = 0; i < terrain->size(); i++)
	{
		terrain->at(i)->Draw();
	}
}


void Game::GenerateTerrain() 
{
	vec2 lastPositionGenerated = START_GENERATE_POSITION;
	vec2 lastChunkSize = vec2(GROUND_CHUNK_SIZE.x , 0.0f);
	bool landPlatformGenerated = false;
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
		}
		else
		{
			groundChunk = new GroundChunk(renderer, gameWorld, lastPositionGenerated + ((GROUND_CHUNK_SIZE + lastChunkSize) * VEC2_MINUS_Y), GROUND_CHUNK_SIZE, false);
			lastChunkSize = vec2(GROUND_CHUNK_SIZE.x, 0.0f);
		}
		i -= groundChunk->GetScale().x;
		lastPositionGenerated = groundChunk->GetPosition();
		terrain->push_back(groundChunk);
	}

	if (!landPlatformGenerated)
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
