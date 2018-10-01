#pragma once
#include "Shape.h" 
class ENGINEDLL_API Circle : public Shape
{
private:
	float * SetVertexPosition(int cantVertx, int radius);
	void SetColorBuffer(float * vertexColor, int cant);
	float * SetVertexColors(int cantVertex);
	int cantVetex;
	unsigned int colorBuffer;
	float * vertexColors;

public:
	Circle(Renderer * renderer);
	~Circle();
	void Draw() override;

};

