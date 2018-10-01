#pragma once
#include "Exports.h"
#include "Renderer.h"
#include "Window.h"

class ENGINEDLL_API GameBase
{
protected:
	virtual bool onStart() = 0;
	virtual bool onStop() = 0;
	virtual bool onUpdate() = 0;
	virtual	bool OnDraw() = 0;

public:
	Renderer * renderer;
	Window * window;
	bool start();
	bool stop();
	void loop();

	bool gameover;
	GameBase();
	~GameBase();
};

