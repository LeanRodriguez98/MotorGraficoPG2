#pragma once
#include "Exports.h"
#include "Shape.h"
#include "Animation.h"

class ENGINEDLL_API Sprite :public Shape
{
	const char* file;

	int textreVertexCount;
	Animation * animation;
public:
	Sprite(Renderer * render, int _cantFrames);
	~Sprite();
	void SetTextureVertices(float* _vertex, int _cant);
	void LoadTexture(const char* _name);
	void Draw() override;
	void DrawMesh(int _drawType) override;
	void Update();
};

