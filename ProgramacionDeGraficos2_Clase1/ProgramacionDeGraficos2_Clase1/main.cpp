#include "Game.h"
#include <iostream>
using namespace std;
int main() 
{
	Game * game = new Game();
	
	//Todo Startup
	if (game->start())
	{
		game->loop();
	}
	game->stop();
	delete game;
	cin.get();
	return 0;
}