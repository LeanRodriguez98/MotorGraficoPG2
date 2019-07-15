#include "Camera.h"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>


Camera::Camera(Renderer * _renderer) : Component(_renderer)
{
	type: ComponentType::CameraComponent;
	renderer = _renderer;

	right = glm::vec4(1, 0, 0, 0);
	up = glm::vec4(0, 1, 0, 0);
	forward = glm::vec4(0, 0, 1, 0);

	cameraPosition = glm::vec4(0, 0, -50, 1);
	point = (cameraPosition + forward);
	upVector = up;
	viewMatrix = glm::lookAt((vec3)cameraPosition,(vec3)point,(vec3)upVector);

	nearDistance = 0.1f;
	farDistance = 10000.0f;
	aspectRatio = 4.0f / 3.0f;
	angle = glm::radians(45.0f);

	renderer->SetProjectionPerspective(angle, aspectRatio, nearDistance, farDistance);
	SetCameraInternals();
	SetCameraDefinitions();
	renderer->SetViewMatrix(viewMatrix);
}

void Camera::CameraWalk(float _direction)
{
	cameraPosition = glm::translate(glm::mat4(1.0f), (glm::vec3)(forward * _direction)) * cameraPosition;
	viewMatrix = glm::lookAt((vec3)cameraPosition,(vec3)(cameraPosition + forward),(vec3)up);

	SetCameraDefinitions();
	renderer->SetViewMatrix(viewMatrix);
}

void Camera::CameraStrafe(float _direction)
{
	cameraPosition = glm::translate(glm::mat4(1.0f), (glm::vec3)(right * _direction)) * cameraPosition;

	viewMatrix = glm::lookAt((vec3)cameraPosition,(vec3)(cameraPosition + forward),(vec3)up);

	SetCameraDefinitions();
	renderer->SetViewMatrix(viewMatrix);
}

void Camera::CameraTranslate(glm::vec3 _direction)
{
	cameraPosition = glm::translate(glm::mat4(1.0f), (glm::vec3)((right * _direction.x) + (forward * _direction.z))) * cameraPosition;

	viewMatrix = glm::lookAt((vec3)cameraPosition,(vec3)(cameraPosition + forward),(vec3)up);

	SetCameraDefinitions();
	renderer->SetViewMatrix(viewMatrix);
}

void Camera::CameraPitch(float _degrees)
{
	forward = glm::rotate(glm::mat4(1.0f), _degrees, glm::vec3(right.x, right.y, right.z)) * forward;
	up = glm::rotate(glm::mat4(1.0f), _degrees, glm::vec3(right.x, right.y, right.z)) * up;

	viewMatrix = glm::lookAt((vec3)cameraPosition,(vec3)(cameraPosition + forward),(vec3)up);

	SetCameraDefinitions();
	renderer->SetViewMatrix(viewMatrix);
}

void Camera::CameraYaw(float _degrees)
{
	forward = glm::rotate(glm::mat4(1.0f), _degrees, glm::vec3(up.x, up.y, up.z)) * forward;
	right = glm::rotate(glm::mat4(1.0f), _degrees, glm::vec3(up.x, up.y, up.z)) * right;

	viewMatrix = glm::lookAt((vec3)cameraPosition,(vec3)(cameraPosition + forward),(vec3)up);

	SetCameraDefinitions();
	renderer->SetViewMatrix(viewMatrix);
}

void Camera::CameraRoll(float _degrees)
{
	right = rotate(mat4(1.0f), _degrees, vec3(forward.x, forward.y, forward.z)) * right;
	up = rotate(mat4(1.0f), _degrees, vec3(forward.x, forward.y, forward.z)) * up;

	viewMatrix = lookAt((vec3)cameraPosition,(vec3)(cameraPosition + forward),(vec3)up);

	SetCameraDefinitions();
	renderer->SetViewMatrix(viewMatrix);
}

void Camera::SetCameraInternals()
{
	tang = tan(angle * 0.5f);
	nearHight = nearDistance * tang;
	nearWidht = nearHight * aspectRatio;
}

void Camera::SetCameraDefinitions()
{
	vec3 rightFrustrum = (vec3)right;
	vec3 upFrustrum = (vec3)up;

	vec3 nearCenter = (vec3)cameraPosition + (vec3)forward * nearDistance;
	vec3 farCenter = (vec3)cameraPosition + (vec3)forward * farDistance;

	vec3 leftPlaneVec = (nearCenter - rightFrustrum * nearWidht) - (vec3)cameraPosition;
	vec3 rightPlaneVec = (nearCenter + rightFrustrum * nearWidht) - (vec3)cameraPosition;
	vec3 topPlaneVec = (nearCenter + upFrustrum * nearHight) - (vec3)cameraPosition;
	vec3 bottomPlaneVec = (nearCenter - upFrustrum * nearHight) - (vec3)cameraPosition;

	vec3 normalLeft = glm::normalize(glm::cross(leftPlaneVec, upFrustrum));
	vec3 normalRight = -glm::normalize(glm::cross(rightPlaneVec, upFrustrum));
	vec3 normalTop = glm::normalize(glm::cross(topPlaneVec, rightFrustrum));
	vec3 normalBottom = -glm::normalize(glm::cross(bottomPlaneVec, rightFrustrum));

	planes[NEARP] = GeneratePlane(-(vec3)forward, nearCenter);
	planes[FARP] = GeneratePlane((vec3)forward, farCenter);
	planes[LEFT] = GeneratePlane(normalLeft, (vec3)cameraPosition);
	planes[RIGHT] = GeneratePlane(normalRight, (vec3)cameraPosition);
	planes[TOP] = GeneratePlane(normalTop, (vec3)cameraPosition);
	planes[BOTTOM] = GeneratePlane(normalBottom, (vec3)cameraPosition);

}

glm::vec4 Camera::GeneratePlane(glm::vec3 _normal, glm::vec3 _point)
{
	glm::vec4 plane;

	plane.x = _normal.x;
	plane.y = _normal.y;
	plane.z = _normal.z;
	plane.w = -glm::dot(_normal, _point);

	return plane;
}

bool Camera::BoxInFrustum(BoundingBox3D * _boundingBox3D)
{
	if (!_boundingBox3D->loaded)
	{
		return true;
	}

	bool isInsideFrustum = true;
	bool allOutsideCurrentPlane = false;
	for (int i = 0; i < (int)Planes::COUNT; i++)
	{
		allOutsideCurrentPlane = false;
		float dist[8];

		for (int j = 0; j < 8; j++)
		{
			vec3 vertexPosition = _boundingBox3D->GetVertex(j);
			vec3 planeNormal = glm::vec3(planes[i]);

			dist[j] = glm::dot(planeNormal, vertexPosition) + planes[i].w;
			if (dist[j] < 0.0f)
				break;
			if (j == CANT_BOUNDING_BOX_VERTEX - 1)
			{
				allOutsideCurrentPlane = true;
			}
		}
		if (allOutsideCurrentPlane)
		{
			isInsideFrustum = false;
			break;
		}
	}
	return isInsideFrustum;
}

Camera::~Camera()
{
}

