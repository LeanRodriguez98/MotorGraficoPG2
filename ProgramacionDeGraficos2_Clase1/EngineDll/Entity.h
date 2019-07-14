#pragma once
#include "Exports.h"
#include "Renderer.h"
#include "Definitions.h"
#include "Collider.h"
#include "Material.h"
#include "TextureImporter.h"
#include<iostream>
using namespace std;
using namespace glm;
class ENGINEDLL_API Entity
{
private:
	vec3 translationVector;
	vec3 rotationVector;
	vec3 scaleVector;
	float height;
	float width;
	vec3 pivotPosition;
	Layers layer;
	Collider * collider;
protected:
	Renderer * renderer;
	mat4 model;
	mat4 translationMatrix;
	mat4 rotationMatrix;
	mat4 scaleMatrix;
	void UpdateModel();
	Material * material;
	BMPData header;
public:

	Entity(Renderer * renderer);
	virtual void Draw() = 0;
	void SetTranslation(float x, float y, float z);
	void SetTranslationX(float x);
	void SetTranslationY(float y);
	void SetTranslationZ(float z);
	void SetRotation(float x, float y, float z);
	void SetRotationX(float x);
	void SetRotationY(float y);
	void SetRotationZ(float z);
	void SetScale(float x, float y, float z);
	void SetScaleX(float x);
	void SetScaleY(float y);
	void SetScaleZ(float z);
	vec3 GetTranslation();
	float GetTranslationX();
	float GetTranslationY();
	float GetTranslationZ();
	vec3 GetRotation();
	float GetRotationX();
	float GetRotationY();
	float GetRotationZ();
	vec3 GetScale();
	float GetScaleX();
	float GetScaleY();
	float GetScaleZ();

	void SetCollider(vec3 _position, float _height, float _width, Layers _layer, bool _isStatic);
	unsigned int GetColliderPivotX();
	unsigned int GetColliderPivotY();
	vec2 GetColliderPivot();
	unsigned int GetColliderHeight();
	unsigned int GetColliderWidth();
	Layers GetColliderLayer();
	bool GetColliderIsStatic();
};

