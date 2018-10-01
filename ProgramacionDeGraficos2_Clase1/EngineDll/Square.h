#pragma once
#include "Shape.h"
#include "Material.h"
class ENGINEDLL_API Square : public Shape
{
private:
	float * vertexColors;
	unsigned int colorBuffer;
	void SetColorBuffer(float * vertexColor, int cant);
public:
	Square(Renderer * renderer);
	~Square();
	void Draw() override;
};