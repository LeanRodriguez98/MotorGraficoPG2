#pragma once
#include "Exports.h"
#include "Entity.h"
#include "Material.h"
#include "Definitions.h"
#include "../external/glm-0.9.9.0/glm/glm.hpp"
#include "../external/glm-0.9.9.0/glm/gtc/matrix_transform.hpp"
using namespace std;
using namespace glm;
class ENGINEDLL_API Component : public Entity
{
public:
	ComponentType type;

	void Update();
	void Draw();
	Component(Renderer * render);
	~Component();
};

