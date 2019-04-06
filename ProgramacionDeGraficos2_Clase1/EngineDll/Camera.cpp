#include "Camera.h"
#include "Time.h"
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
	cameraPosition += vec3(0.0f, 0.0f, _directionMatrix * Time::dt);
	UpdateViewMatrix();

}
void Camera::CameraStrafe(float _directionMatrix)
{
	cameraPosition += vec3(_directionMatrix * Time::dt,0.0f, 0.0f);
	UpdateViewMatrix();
}

void Camera::UpdateViewMatrix() 
{
	renderer->SetViewMatrix(cameraPosition, cameraRotation,up);
}

void Camera::CameraRoll(float _rotationMatrix)
{
	mat4 rotationMatrix = rotate(mat4(1.0f), _rotationMatrix, right);
	cameraRotation *= rotationMatrix;
	UpdateViewMatrix();

}
void Camera::CameraYaw(float _rotationMatrix)
{
	mat4 rotationMatrix = rotate(mat4(1.0f), _rotationMatrix, up);
	cameraRotation *= rotationMatrix;
	UpdateViewMatrix();


}
void Camera::CameraPitch(float _rotationMatrix)
{
	mat4 rotationMatrix = rotate(mat4(1.0f), _rotationMatrix, foward);
	cameraRotation *= rotationMatrix;
	UpdateViewMatrix();


}