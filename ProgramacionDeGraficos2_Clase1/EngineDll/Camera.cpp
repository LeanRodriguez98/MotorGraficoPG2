#include "Camera.h"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>


Camera::Camera(Renderer *_renderer)
{
	renderer = _renderer;
	eyePosition = vec3(0.0f, 0.0f, 10.0f);
	upVector = vec3(0.0f, 1.0f, 0.0f);


	forward = vec4(0.0f, 0.0f, -1.0f, 0.0f);
	right = vec4(1.0f, 0.0f, 0.0f, 0.0f);
	up = vec4(0.0f, 1.0f, 0.0f, 0.0f);

	cameraPosition = eyePosition + (vec3)forward;
}

Camera::~Camera()
{
}

void Camera::UpdateViewMatrix()
{
	renderer->SetViewMatrix(eyePosition, cameraPosition, upVector);
}
void Camera::CameraWalk(float _direction)
{
	cameraPosition += (vec3)forward * _direction;
	eyePosition += (vec3)forward * _direction;
	UpdateViewMatrix();
}
void Camera::CameraStrafe(float _direction)
{
	cameraPosition += (vec3)right * _direction;
	eyePosition += (vec3)right * _direction;
	UpdateViewMatrix();
}
void Camera::CameraPitch(float _direction)
{
	forward = rotate(mat4(1.0f), _direction, vec3(right.x, right.y, right.z)) * forward;
	up = rotate(mat4(1.0f), _direction, vec3(right.x, right.y, right.z)) * up;

	upVector = (vec3)up;
	cameraPosition = eyePosition + (vec3)forward;
	UpdateViewMatrix();
}
void Camera::CameraYaw(float _direction)
{
	forward = rotate(mat4(1.0f), _direction, vec3(upVector.x, upVector.y, upVector.z)) * forward;
	right = rotate(mat4(1.0f), _direction, vec3(upVector.x, upVector.y, upVector.z)) * right;

	upVector = (vec3)up;
	cameraPosition = eyePosition + (vec3)forward;
	UpdateViewMatrix();
}
void Camera::CameraRoll(float _direction)
{
	mat4 auxRotation = rotate(mat4(1.0f), _direction, vec3(forward.x, forward.y, forward.z));
	right = auxRotation * right;
	up = auxRotation * up;

	upVector = (vec3)up;
	cameraPosition = eyePosition + (vec3)forward;
	UpdateViewMatrix();
}