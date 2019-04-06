#pragma once
#include "Exports.h"
#include "Renderer.h"
using namespace glm;


class ENGINEDLL_API Camera
{
private:
	Renderer * renderer;
	vec3 cameraPosition;
	vec3 cameraRotation;
	vec3 foward;
	vec3 right;
	vec3 up;

public:
	Camera(Renderer * _renderer);
	~Camera();
	void CameraWalk(float _directionMatrix);
	void CameraStrafe(float _directionMatrix);
	void CameraRoll(float _rotationMatrix);
	void CameraYaw(float _rotationMatrix);
	void CameraPitch(float _rotationMatrix);
	void UpdateViewMatrix();
};