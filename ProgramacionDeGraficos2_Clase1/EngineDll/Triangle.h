#pragma once
#include "Shape.h"
#include "Material.h"
class ENGINEDLL_API Triangle:public Shape
{
private:
	
public:
	Triangle(Renderer * renderer);
	~Triangle();
	void Draw() override;
};

