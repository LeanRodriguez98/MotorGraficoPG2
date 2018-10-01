#pragma once
#include "../EngineDll/GameBase.h"
#include "../EngineDll/Renderer.h"
#include "../EngineDll/Triangle.h"
#include "../EngineDll/Square.h"
#include "../EngineDll/Circle.h"

class Game :public GameBase
{
private:
	Triangle * triangle_1;
	Square * square_1;
	Circle * circle_1;
	Material * material1;
	Material * material2;
protected:
	bool onStart() override;
	bool onStop() override;
	bool onUpdate() override;
	bool OnDraw() override;

public:
	int i;
	Game();
	~Game();
};

