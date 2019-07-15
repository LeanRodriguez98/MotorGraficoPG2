// http://www.lighthouse3d.com/tutorials/view-frustum-culling/
#pragma once
#include "Exports.h"
#include "Renderer.h"
#include "Component.h"
#include "Definitions.h"
#include "BoundingBox3D.h"
using namespace glm;

class ENGINEDLL_API Camera : public Component {
private:
	Renderer * renderer;
	mat4 viewMatrix;
	vec4 right;
	vec4 up;
	vec4 forward;
	vec4 cameraPosition;
	vec4 upVector;
	vec4 point;
	vec4 planes[COUNT];

	vec3 nearTopLeft;
	vec3 nearTopRight;
	vec3 nearBottomLeft;
	vec3 nearBottomRight;
	vec3 farTopLeft;
	vec3 farTopRight;
	vec3 farBottomLeft;
	vec3 farBottomRight;

	float nearDistance;
	float farDistance;
	float aspectRatio;
	float angle;
	float tang;
	float nearWidht;
	float nearHight;

public:
	void CameraWalk(float _direction);
	void CameraStrafe(float _direction);
	void CameraTranslate(vec3 _direction);
	void CameraPitch(float _degrees);
	void CameraYaw(float _degrees);
	void CameraRoll(float _degrees);
	void SetCameraInternals();
	void SetCameraDefinitions();
	vec4 GeneratePlane(vec3 _normal, vec3 _point);
	bool BoxInFrustum(BoundingBox3D * _boundingBox3D);
	Camera(Renderer * _renderer);
	~Camera();
};

