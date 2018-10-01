#include "Entity.h"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>

Entity::Entity(Renderer * _renderer)
{
	renderer = _renderer;
	model = mat4(1.0f);
	translationVector = vec3(0.0f, 0.0f, 0.0f);
	rotationVector = vec3(0.0f, 0.0f, 0.0f);
	scaleVector = vec3(1.0f, 1.0f, 1.0f);
	translationMatrix = mat4(1.0f);
	rotationMatrix = mat4(1.0f);
	scaleMatrix = mat4(1.0f);
}

Entity::~Entity()
{
}

void Entity::SetTranslation(float x, float y, float z)
{
	translationVector[0] = x;
	translationVector[1] = y;
	translationVector[2] = z;

	translationMatrix = translate(mat4(1.0f), translationVector);
	UpdateModel();
}

void Entity::SetRotationX(float x)
{
	rotationVector[0] = x;
	rotationMatrix = rotate(mat4(1.0f), x, vec3(1, 0, 0));
	UpdateModel();
}

void Entity::SetRotationY(float y)
{
	rotationVector[1] = y;
	rotationMatrix = rotate(mat4(1.0f), y, vec3(0, 1, 0));
	UpdateModel();
}

void Entity::SetRotationZ(float z)
{
	rotationVector[2] = z;
	rotationMatrix = rotate(mat4(1.0f), z, vec3(0, 0, 1));
	UpdateModel();
}

void Entity::SetScale(float x, float y, float z)
{
	scaleVector[0] = x;
	scaleVector[1] = y;
	scaleVector[2] = z;

	scaleMatrix = scale(mat4(1.0f), scaleVector);
	UpdateModel();
}

void Entity::UpdateModel()
{
	model = translationMatrix * rotationMatrix * scaleMatrix;
}
