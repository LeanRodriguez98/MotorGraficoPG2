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

	/*Frustum*/
	enum Planes {
		TOP = 0, BOTTOM, LEFT,
		RIGHT, NEARP, FARP, COUNT
	};

	glm::vec4 pl[COUNT];

	glm::vec3 ntl, ntr, nbl, nbr, ftl, ftr, fbl, fbr;

	float nearD, farD, ratio, angle, tang;
	float nw, nh, fw, fh;
public:
	void CameraWalk(float _direction);
	void CameraStrafe(float _direction);
	void CameraTranslate(glm::vec3 _direction);

	void CameraPitch(float _degrees);
	void CameraYaw(float _degrees);
	void CameraRoll(float _degrees);

	/*Frustum culling*/
	void setCamInternals();
	void setCamDef();
	vec4 GeneratePlane(vec3 _normal, vec3 _point);
	bool BoxInFrustum(BoundingBox3D * _boundingBox3D);

	Camera(Renderer * _renderer);
	~Camera();
};


