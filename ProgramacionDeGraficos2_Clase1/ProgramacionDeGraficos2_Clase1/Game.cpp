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
	gameWorld = new b2World(b2Vec2(0.0f, -9.81f));

	player1 = new Player(renderer,9,PLAYER_SPEED,1.6f,1.0f,0,0,0,NULL);

	Material * m1 = new Material();
	unsigned int ProgramID = m1->LoadShaders("colorvertexshader.txt", "colorfragmentshader.txt");

	terrain = new vector<GroundChunk*>();

	GenerateTerrain();

	ship = new Ship(renderer, gameWorld, vec2(0.0f, 6.0f), vec2(0.4f,0.4f));

	return true;
}
bool Game::OnStop() {

	delete player1;
	delete ship;
	for (int i = 0; i < terrain->size(); i++)
	{
		delete terrain->at(i);
	}
	return false;
}
bool Game::OnUpdate() {

	player1->Update();
	
	UpdatePhisics();

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
	for (float i = SCREEN_WIDHT; i > 0; i+=0)
	{
		GroundChunk * groundChunk;

		if (rand() % 2 != 0)
		{
			groundChunk = new GroundChunk(renderer, gameWorld, lastPositionGenerated + (GROUND_CHUNK_SIZE * VEC2_X2), GROUND_CHUNK_SIZE);
		}
		else
		{
			groundChunk = new GroundChunk(renderer, gameWorld, lastPositionGenerated + (GROUND_CHUNK_SIZE * VEC2_X2_MINUS_Y), GROUND_CHUNK_SIZE);
		}
		i -= groundChunk->GetScale().x;
		lastPositionGenerated = groundChunk->GetPosition();
		terrain->push_back(groundChunk);
	}
}

void Game::UpdatePhisics() 
{
	gameWorld->Step(Time::dt, 8, 8);
	gameWorld->ClearForces();
}
