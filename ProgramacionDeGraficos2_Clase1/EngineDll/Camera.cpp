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
void Camera::CameraWalk(float direction)
{
	cameraPosition += (vec3)forward * direction;
	eyePosition += (vec3)forward * direction;
	UpdateViewMatrix();
}
void Camera::CameraStrafe(float direction)
{
	cameraPosition += (vec3)right * direction;
	eyePosition += (vec3)right * direction;
	UpdateViewMatrix();
}
void Camera::CameraPitch(float direction)
{
	forward = glm::rotate(mat4(1.0f), direction, vec3(right.x, right.y, right.z)) * forward;
	up = glm::rotate(mat4(1.0f), direction, vec3(right.x, right.y, right.z)) * up;

	upVector = (vec3)up;
	cameraPosition = eyePosition + (vec3)forward;
	UpdateViewMatrix();
}
void Camera::CameraYaw(float direction)
{
	forward = glm::rotate(mat4(1.0f), direction, vec3(upVector.x, upVector.y, upVector.z)) * forward;
	right = glm::rotate(mat4(1.0f), direction, vec3(upVector.x, upVector.y, upVector.z)) * right;

	upVector = (vec3)up;
	cameraPosition = eyePosition + (vec3)forward;
	UpdateViewMatrix();
}
void Camera::CameraRoll(float direction)
{
	mat4 rot = rotate(mat4(1.0f), direction, vec3(forward.x, forward.y, forward.z));
	right = rot * right;
	up = rot * up;

	upVector = (vec3)up;
	cameraPosition = eyePosition + (vec3)forward;
	UpdateViewMatrix();
}