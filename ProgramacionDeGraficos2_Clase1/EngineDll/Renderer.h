#pragma once
#include "Exports.h"
#include "Window.h"
#include "../external/glm-0.9.9.0/glm/glm.hpp"
#include "../external/glm-0.9.9.0/glm/gtc/matrix_transform.hpp"
#define PRIMITIVE_TRIANGLE 0x0004
#define PRIMITIVE_TRIANGLE_STRIP 0x0005
#define PRIMITIVE_TRIANGLE_FAN 0x0006
using namespace glm;
using namespace std;
class ENGINEDLL_API Renderer
{
private:
	Window * _window;
	void * VertexArray;
	mat4 modelMatrix;
	mat4 viewMatrix;
	mat4 projectionMatrix;
	mat4 modelViewProjectionMatrix;
public:
	Renderer();
	~Renderer();
	bool Start(Window * window);
	bool Stop();
	void SetClearColor(float r, float g, float b, float a);
	void SwapBuffer();
	void ClearWindow();
	unsigned int GenerateVertexBuffer(float * buffer, int size);
	unsigned int GenerateColorBuffer(float * buffer, int size);
	void EnableVertexAttribute(unsigned int attribute);
	void BindBuffer(unsigned int buffer, unsigned int attribute);
	void DrawArrayBuffers(int drawSystem,int size);
	void DisableVertexAttribute(unsigned int attribute);
	void UpdateModelViewProjectionMatrix();
	void SetModel(mat4 model);
	void LoadIdentityMatrix();
	void MultiplyModel(mat4 model);
	mat4& GetModelViewProjectionMatrix();
};

