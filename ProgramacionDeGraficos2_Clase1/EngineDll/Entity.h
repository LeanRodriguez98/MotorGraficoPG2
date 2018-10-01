#pragma once
#include "Renderer.h"
class ENGINEDLL_API Entity
{
private:
	vec3 translationVector;
	vec3 rotationVector;
	vec3 scaleVector;
protected:
	Renderer * renderer;
	mat4 model;
	mat4 translationMatrix;
	mat4 rotationMatrix;
	mat4 scaleMatrix;
	void UpdateModel();
	virtual void Draw() = 0;
public:
	Entity(Renderer * _renderer);
	~Entity();
	void SetTranslation(float x, float y, float z);
	void SetRotationX(float x);
	void SetRotationY(float y);
	void SetRotationZ(float z);
	void SetScale(float x, float y, float z);
};

