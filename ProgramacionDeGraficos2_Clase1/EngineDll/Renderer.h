#pragma once
#include "Exports.h"
#include "Window.h"
#include "../external/glm-0.9.9.0/glm/glm.hpp"
#include "../external/glm-0.9.9.0/glm/gtc/matrix_transform.hpp"

#include <iostream>
#include <vector>
using namespace std;
using namespace glm;
class ENGINEDLL_API Renderer
{
private:
	unsigned int VertexArray;
	mat4 modelMatrix;
	mat4 viewMatrix;
	mat4 projectionMatrix;
	mat4 modelViewProjectionMatrix;

public:
	Renderer();
	~Renderer();
	bool Start(Window *windowPTR);
	bool Stop();
	void ClearWindow();
	void SetClearColor(float r, float g, float b, float a);
	void SwapBuffer();
	unsigned int  GenerateBuffer(float* buffer, int size);
	unsigned int  GenerateColorBuffer(float* buffer, int size);
	unsigned int GenerateTextureBuffer(int width, int height, unsigned char* data);
	unsigned int GenerateIndexBuffer(unsigned int* buffer, int size);
	unsigned int GenerateIndexBuffer(vector<unsigned int> index);
	void BindBuffer(unsigned int vtxbuffer, unsigned int name);
	void BindColorBuffer(unsigned int clrbuffer, unsigned int name);
	void BindTextureBuffer(unsigned int txtrebuffer, unsigned int name);
	void BindMeshBuffer(unsigned int indexbuffer);
	void EnableVertexAttribute(unsigned int name);
	void DisableVertexAttribute(unsigned int name);
	void DrawArrayBuffers(int size, int drawType);
	void DrawIndexBuffer(int indexcount);

	void DestroyBuffer(unsigned int buffer);
	void UpdateModelViewProjectionMatrix();
	mat4&  GetModelViewProjectionMatrix();
	mat4 GetViewMatrix();
	void LoadIdentityMatrix();
	void MultiplyModelMatrix(mat4 mat);
	void MultiplyWorldMatrix(mat4 mat);
	void CameraFollow(vec3 _playerPosition);
	Window * window;
	void SetProjectionOrtho(float _left, float _right, float _bottom, float _top, float _zNear, float _zFar);
	void SetProjectionPerspective(float _fovy, float _aspect, float _zNear, float _zFar);
	void SetViewMatrix(vec3 _eye, vec3 _center, vec3 _up);
	void SetViewMatrix(mat4 _viewMatrix);
};
