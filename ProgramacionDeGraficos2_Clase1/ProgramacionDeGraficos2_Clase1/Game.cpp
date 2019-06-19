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

	Material * m1 = new Material();
	unsigned int ProgramID = m1->LoadShaders("colorvertexshader.txt", "colorfragmentshader.txt");

	sqr = new Square(renderer);
	sqr->SetMaterial(m1);
	sqr->SetTranslation(-8, -8, 0);
	sqr->SetScale(1, 0.2, 0);


	sqr2 = new Square(renderer);
	sqr2->SetMaterial(m1);
	sqr2->SetTranslation(-7, -7.6, 0);
	sqr2->SetScale(1, 0.2, 0);
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
		sqr->Draw();
		sqr2->Draw();

}

