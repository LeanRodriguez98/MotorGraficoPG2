#include "Game.h"



Game::Game()
{
}


Game::~Game()
{
}


bool Game::onStart()
{
	i = 0;
	material1 = new Material();
	material2 = new Material();
	unsigned int ProgramID = material1->LoadShaders("colorvertexshader.txt", "colorfragmentshader.txt");
	unsigned int ProgramID2 = material2->LoadShaders("vertexshader.txt", "fragmentshader.txt");

	square_1 = new Square(renderer);
	square_1->SetMaterial(material1);
	square_1->SetTranslation(-5, 0, 0);
	square_1->SetScale(3, 3, 0);

	triangle_1 = new Triangle(renderer);
	triangle_1->SetMaterial(material2);
	triangle_1->SetTranslation(5, 0, 0);
	triangle_1->SetScale(3, 3, 0);

	circle_1 = new Circle(renderer);
	circle_1->SetMaterial(material1);

	return true;
}

bool Game::onStop()
{
	return false;
}

bool Game::onUpdate()
{
	i++;
	
	if (i < 100000000)
	{
		circle_1->SetRotationZ(i / 50);
		triangle_1->SetRotationZ(i / 50);
		square_1->SetRotationZ(i / 50);
		return false;
	}
	else
	{
		return true;
	}

}

bool Game::OnDraw() 
{
	triangle_1->Draw();
	square_1->Draw();
	circle_1->Draw();
	return true;
}

