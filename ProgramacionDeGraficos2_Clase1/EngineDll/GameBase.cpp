#include "Gamebase.h"

Gamebase::Gamebase() {

}
Gamebase::~Gamebase() {
}
bool Gamebase::Start() {

	window = new Window();
	if (!window->Start(800, 600, " "))
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


