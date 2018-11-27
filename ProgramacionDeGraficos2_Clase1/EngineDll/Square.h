#pragma once
#include "Shape.h"
#include "Material.h"
class ENGINEDLL_API Square :public Shape
{
public:
	Square(Renderer *render);
	~Square();
	void Draw() override;
};

