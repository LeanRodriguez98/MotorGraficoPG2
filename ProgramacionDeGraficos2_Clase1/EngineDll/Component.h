#pragma once
#include "Exports.h"
#include "Entity.h"
#include "Material.h"
#include "Definitions.h"
#include<glm/glm.hpp>
#include<glm\gtc\matrix_transform.hpp>
using namespace std;
using namespace glm;
class ENGINEDLL_API Component : public Entity
{
public:
	ComponentsType type;

	void Update(glm::mat4 ViewMatrix);
	void Draw();
	Component(Renderer * render);
	~Component();
};

