#include "GameBase.h"
#include "TypeDefs.h"
#include <iostream>

GameBase::GameBase()
{
	renderer = new Renderer;
}


GameBase::~GameBase()
{
	delete renderer;
}

bool GameBase::start()
{
	window = new Window(800, 600,  (char *)"window");
	window->start();

	if (!renderer->Start(window))
	{
		cout << "no se pudo iniciar el renderer" << endl;
		cin.get();
		return false;
	}

	renderer->SetClearColor(0.5f,0.5f,0.5f,1);

	return onStart();

}

bool GameBase::stop()
{
	onStop();
	if (!renderer->Stop())
	{
		cout << "no se pudo detener el renderer" << endl;
		cin.get();
		return false;
	}
	window->stop();
	return true;
}

void GameBase::loop() 
{
	gameover = false;
	while (!gameover && (!window->ShouldClose()))
	{
		gameover = onUpdate();
		renderer->ClearWindow();
		OnDraw();
		renderer->SwapBuffer();
		window->PollEvents();

	}
}
