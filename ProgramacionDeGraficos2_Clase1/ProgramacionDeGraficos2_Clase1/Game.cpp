#include "Game.h"
#include <Box2D/Box2D.h>
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

	
	terrain = new vector<Square*>();

	for (int i = 0; i < 19; i++)
	{
		Square * sqr = new Square(renderer);
		sqr->SetMaterial(m1);
		sqr->SetScale(1, 0.2, 0);
		sqr->SetTranslation(-9 + (i * sqr->GetScaleX()), -8 + (sqr->GetScaleY()* 2 * i), 0);

		/*if (i % 2 == 0)
		{

		}
		else
		{
			sqr->SetTranslation(-9 + (i * 2), -8 - (0.2*i), 0);

		}*/
		terrain->push_back(sqr);
	}

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
		for (int i = 0; i < terrain->size(); i++)
		{
			terrain->at(i)->Draw();
		}

}

