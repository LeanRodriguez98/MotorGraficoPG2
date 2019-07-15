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
	viewMatrix = glm::lookAt(
		(glm::vec3)cameraPosition,
		(glm::vec3)point,
		(glm::vec3)upVector
	);

	nearD = 0.1f;
	farD = 10000.0f;
	ratio = 4.0f / 3.0f;
	angle = glm::radians(45.0f);

	renderer->SetProjectionPerspective(angle, ratio, nearD, farD);
	setCamInternals();
	setCamDef();
	renderer->SetViewMatrix(viewMatrix);
}

void Camera::CameraWalk(float _direction)
{
	cameraPosition = glm::translate(glm::mat4(1.0f), (glm::vec3)(forward * _direction)) * cameraPosition;
	viewMatrix = glm::lookAt(
		(glm::vec3)cameraPosition,
		(glm::vec3)(cameraPosition + forward),
		(glm::vec3)up
	);

	setCamDef();
	renderer->SetViewMatrix(viewMatrix);
}

void Camera::CameraStrafe(float _direction)
{
	cameraPosition = glm::translate(glm::mat4(1.0f), (glm::vec3)(right * _direction)) * cameraPosition;

	viewMatrix = glm::lookAt(
		(glm::vec3)cameraPosition,
		(glm::vec3)(cameraPosition + forward),
		(glm::vec3)up
	);

	setCamDef();
	renderer->SetViewMatrix(viewMatrix);
}

void Camera::CameraTranslate(glm::vec3 _direction)
{
	cameraPosition = glm::translate(glm::mat4(1.0f), (glm::vec3)((right * _direction.x) + (forward * _direction.z))) * cameraPosition;

	viewMatrix = glm::lookAt(
		(glm::vec3)cameraPosition,
		(glm::vec3)(cameraPosition + forward),
		(glm::vec3)up
	);

	setCamDef();
	renderer->SetViewMatrix(viewMatrix);
}

void Camera::CameraPitch(float _degrees)
{
	forward = glm::rotate(glm::mat4(1.0f), _degrees, glm::vec3(right.x, right.y, right.z)) * forward;
	up = glm::rotate(glm::mat4(1.0f), _degrees, glm::vec3(right.x, right.y, right.z)) * up;

	viewMatrix = glm::lookAt(
		(glm::vec3)cameraPosition,
		(glm::vec3)(cameraPosition + forward),
		(glm::vec3)up
	);

	setCamDef();
	renderer->SetViewMatrix(viewMatrix);
}

void Camera::CameraYaw(float _degrees)
{
	forward = glm::rotate(glm::mat4(1.0f), _degrees, glm::vec3(up.x, up.y, up.z)) * forward;
	right = glm::rotate(glm::mat4(1.0f), _degrees, glm::vec3(up.x, up.y, up.z)) * right;

	viewMatrix = glm::lookAt(
		(glm::vec3)cameraPosition,
		(glm::vec3)(cameraPosition + forward),
		(glm::vec3)up
	);

	setCamDef();
	renderer->SetViewMatrix(viewMatrix);
}

void Camera::CameraRoll(float _degrees)
{
	right = glm::rotate(glm::mat4(1.0f), _degrees, glm::vec3(forward.x, forward.y, forward.z)) * right;
	up = glm::rotate(glm::mat4(1.0f), _degrees, glm::vec3(forward.x, forward.y, forward.z)) * up;

	viewMatrix = glm::lookAt(
		(glm::vec3)cameraPosition,
		(glm::vec3)(cameraPosition + forward),
		(glm::vec3)up
	);

	setCamDef();
	renderer->SetViewMatrix(viewMatrix);
}



void Camera::setCamInternals()
{
	tang = glm::tan(angle * 0.5f);
	nh = nearD * tang;
	nw = nh * ratio;
	fh = farD * tang;
	fw = fh * ratio;
}

void Camera::setCamDef()
{
	glm::vec3 rightFrustrum = (glm::vec3)right;
	glm::vec3 upFrustrum = (glm::vec3)up;

	glm::vec3 nearCenter = (glm::vec3)cameraPosition + (glm::vec3)forward * nearD;
	glm::vec3 farCenter = (glm::vec3)cameraPosition + (glm::vec3)forward * farD;

	glm::vec3 leftPlaneVec = (nearCenter - rightFrustrum * nw) - (glm::vec3)cameraPosition;
	glm::vec3 rightPlaneVec = (nearCenter + rightFrustrum * nw) - (glm::vec3)cameraPosition;
	glm::vec3 topPlaneVec = (nearCenter + upFrustrum * nh) - (glm::vec3)cameraPosition;
	glm::vec3 bottomPlaneVec = (nearCenter - upFrustrum * nh) - (glm::vec3)cameraPosition;

	glm::vec3 normalLeft = glm::normalize(glm::cross(leftPlaneVec, upFrustrum));
	glm::vec3 normalRight = -glm::normalize(glm::cross(rightPlaneVec, upFrustrum));
	glm::vec3 normalTop = glm::normalize(glm::cross(topPlaneVec, rightFrustrum));
	glm::vec3 normalBottom = -glm::normalize(glm::cross(bottomPlaneVec, rightFrustrum));

	pl[NEARP] = GeneratePlane(-(glm::vec3)forward, nearCenter);
	pl[FARP] = GeneratePlane((glm::vec3)forward, farCenter);
	pl[LEFT] = GeneratePlane(normalLeft, (glm::vec3)cameraPosition);
	pl[RIGHT] = GeneratePlane(normalRight, (glm::vec3)cameraPosition);
	pl[TOP] = GeneratePlane(normalTop, (glm::vec3)cameraPosition);
	pl[BOTTOM] = GeneratePlane(normalBottom, (glm::vec3)cameraPosition);
}

glm::vec4 Camera::GeneratePlane(glm::vec3 normal, glm::vec3 point)
{
	glm::vec4 plane;

	plane.x = normal.x;
	plane.y = normal.y;
	plane.z = normal.z;
	plane.w = -glm::dot(normal, point);

	return plane;
}

bool Camera::BoxInFrustum(BoundingBox3D * boundingCube)
{
	bool isInsideFrustum = true;
	bool allOutsideCurrentPlane = false;

	for (int i = 0; i < (int)Planes::COUNT; i++)
	{
		allOutsideCurrentPlane = false;

		for (int j = 0; j < 8; j++)
		{
			glm::vec3 vertexPosition = boundingCube->GetVertex(j);
			glm::vec3 planeNormal = glm::vec3(pl[i]);

			float dist = glm::dot(planeNormal, vertexPosition) + pl[i].w;
			if (dist < 0.0f)
				break;
			if (j == 7)
				allOutsideCurrentPlane = true;
		}
		if (allOutsideCurrentPlane)
		{
			isInsideFrustum = false;
			break;
		}
	}
	if (isInsideFrustum)
		return true;
	else
		return false;
}

Camera::~Camera()
{
}