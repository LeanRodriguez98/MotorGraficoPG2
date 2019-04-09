#include "Camera.h"
#include "Time.h"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>

Camera::Camera(Renderer * _renderer)
{
	renderer = _renderer;
	cameraPosition = vec3(0.0f, 0.0f, 0.0f);
	foward = vec3(0.0f, 0.0f, 1.0f);
	right = vec3(1.0f, 0.0f, 0.0f);
	up = vec3(0.0f, 1.0f, 0.0f);
	cameraRotation = vec3(0.0f, 0.0f, 0.0f) + foward;

}


Camera::~Camera()
{

}


void Camera::CameraWalk(float _directionMatrix) 
{
	cameraPosition += foward * _directionMatrix * Time::dt;
	UpdateViewMatrix();

}
void Camera::CameraStrafe(float _directionMatrix)
{
	cameraPosition += right * _directionMatrix * Time::dt;
	UpdateViewMatrix();
}

void Camera::UpdateViewMatrix() 
{
	renderer->SetViewMatrix(cameraPosition, cameraRotation,up);
}

void Camera::CameraRoll(float _rotationMatrix)
{
	glm::mat4 rot = rotate(glm::mat4(1.0f), (float)(_rotationMatrix * Time::dt), foward);
	glm::vec4 aux = glm::vec4(foward.x, foward.y, foward.z, 0.0f);
	aux = rot * aux;
	foward.x = aux.x;
	foward.y = aux.y;
	foward.z = aux.z;

	aux = glm::vec4(up.x, up.y, up.z, 0.0f);
	aux = rot * aux;
	up.x = aux.x;
	up.y = aux.y;
	up.z = aux.z;

	UpdateViewMatrix();

}
void Camera::CameraYaw(float _rotationMatrix)
{
	glm::mat4 rot = rotate(glm::mat4(1.0f), (float)(_rotationMatrix * Time::dt), up);
	glm::vec4 aux = glm::vec4(foward.x, foward.y, foward.z, 0.0f);
	aux = rot * aux;
	foward.x = aux.x;
	foward.y = aux.y;
	foward.z = aux.z;

	aux = glm::vec4(up.x, up.y, up.z, 0.0f);
	aux = rot * aux;
	up.x = aux.x;
	up.y = aux.y;
	up.z = aux.z;

	UpdateViewMatrix();

}
void Camera::CameraPitch(float _rotationMatrix)
{
	glm::mat4 rot = rotate(glm::mat4(1.0f), (float)(_rotationMatrix * Time::dt), right);
	glm::vec4 aux = glm::vec4(foward.x, foward.y, foward.z, 0.0f);
	aux = rot * aux;
	foward.x = aux.x;
	foward.y = aux.y;
	foward.z = aux.z;

	aux = glm::vec4(up.x, up.y, up.z, 0.0f);
	aux = rot * aux;
	up.x = aux.x;
	up.y = aux.y;
	up.z = aux.z;

	UpdateViewMatrix();


}