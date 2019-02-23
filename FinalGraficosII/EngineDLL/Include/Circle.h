#pragma once
#include "Shape.h"
class  ENGINEDLL_API Circle :public Shape
{
private:
float radius;
int cantTriangles;
public:
Circle(Renderer *render, float _radius, int _cantTriangles);
~Circle();
void Draw() override;
};

