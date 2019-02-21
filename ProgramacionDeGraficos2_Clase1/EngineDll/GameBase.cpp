#include "Gamebase.h"

Gamebase::Gamebase() {

}
Gamebase::~Gamebase() {
}
bool Gamebase::Start() {

	window = new Window();
	if (!window->Start(screenWidth, screenHeight, "Game"))
		return false;

	renderer = new Renderer();
	if (!renderer->Start(window))
		return false;
	renderer->SetClearColor(0.5f, 0.5f, 0.5f, 1);
	return OnStart();
}
void Gamebase::Loop() {
	bool loop = true;
	Time::FirstMeasure();

	while (loop && !window->ShouldClose())
	{
		Time::Measure();

		loop = OnUpdate();
		renderer->ClearWindow();
		OnDraw();
		renderer->SwapBuffer();
		window->PollEvents();
	}
}
bool Gamebase::Stop() {
	OnStop();
	renderer->Stop();
	window->Stop();

	delete renderer;
	delete window;
	return true;
}

void Gamebase::SetScreenHeight(int _screenHeight)
{
	screenHeight = _screenHeight;
}
void Gamebase::SetScreenWidth(int _screenWidth) 
{
	screenWidth = _screenWidth;
}
int Gamebase::GetScreenHeight() 
{
	return screenHeight;
}
int Gamebase::GetScreenWidth() 
{
	return screenWidth;
}

