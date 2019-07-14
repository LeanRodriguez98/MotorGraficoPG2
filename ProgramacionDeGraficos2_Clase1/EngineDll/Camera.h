#include "Exports.h"
#include "Renderer.h"
#include "Component.h"
#include "Definitions.h"
using namespace glm;
class ENGINEDLL_API Camera : public Component
{
private:
	Renderer * renderer;
	vec3 eyePosition;
	vec3 cameraPosition;
	vec3 upVector;

	vec4 forward;
	vec4 right;
	vec4 up;

public:
	Camera(Renderer * renderer);
	~Camera();
	void UpdateViewMatrix();
	void CameraWalk(float direction);
	void CameraStrafe(float direction);
	void CameraPitch(float direction);
	void CameraYaw(float direction);
	void CameraRoll(float direction);

};

