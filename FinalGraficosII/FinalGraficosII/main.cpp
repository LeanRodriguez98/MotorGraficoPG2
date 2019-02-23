#include "Game.h"

int main() {

	Gamebase* game = new Game();

	//TODO: startup
	game->SetScreenWidth(800);
	game->SetScreenHeight(600);
	if (game->Start()) {
		game->Loop();
	}

	game->Stop();

	delete game;
	return 0;
}