#pragma once
#include "Exports.h"
#include "Shape.h"
#include "TextureImporter.h"
#include "Animation.h"

class ENGINEDLL_API Sprite :public Shape
{
	BMPData header;
	const char* file;
	unsigned int textureBufferId;
	unsigned int UVBufferId;
	float *textureUVvertex;
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

