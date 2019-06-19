#include "Game.h"

Game::Game()
{
}
Game::~Game()
{
}
bool Game::OnStart() {
	
	
	ImputManager::GetInstance()->SetWindow(window);

	player1 = new Player(renderer,9,PLAYER_SPEED,1.6f,1.0f,0,0,0,NULL);

	return true;
}
bool Game::OnStop() {

	delete player1;
	return false;
}
bool Game::OnUpdate() {

	player1->Update();
	if (ImputManager::GetInstance()->GetKeyDown(Escape))
	{
		return false;
	}

	
	return true;
}

void Game::OnDraw()
{



		player1->Draw();

}

