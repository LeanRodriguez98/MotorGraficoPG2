#include "Entity.h"
#define GLM_ENABLE_EXPERIMENTAL

Entity::Entity(Renderer *renderPTR)
{
	renderer = renderPTR;
	model = mat4(1.0f);
	translationMatrix = mat4(1.0f);
	rotationMatrix = mat4(1.0f);
	scaleMatrix = mat4(1.0f);
	pivotPosition = vec3(0.0f);

	translationVector[0] = 0.0f;
	translationVector[1] = 0.0f;
	translationVector[2] = 0.0f;

	rotationVector[0] = 0.0f; 
	rotationVector[1] = 0.0f;
	rotationVector[2] = 0.0f;

	scaleVector[0] = 1.0f; 
	scaleVector[1] = 1.0f; 
	scaleVector[2] = 1.0f;

}
void Entity::SetTranslation(float x, float y, float z)
{
	translationVector[0] = x;
	translationVector[1] = y;
	translationVector[2] = z;

	translationMatrix = glm::translate(glm::mat4(1.0f), translationVector);
	UpdateModel();
}


void Entity::SetTranslationX(float x)
{
	translationVector[0] = x;
	translationMatrix = glm::translate(glm::mat4(1.0f), translationVector);
	UpdateModel();
}

void Entity::SetTranslationY(float y)
{
	translationVector[1] = y;
	translationMatrix = glm::translate(glm::mat4(1.0f), translationVector);
	UpdateModel();
}

void Entity::SetTranslationZ(float z)
{
	translationVector[2] = z;
	translationMatrix = glm::translate(glm::mat4(1.0f), translationVector);
	UpdateModel();
}

void Entity::SetRotation(float x, float y, float z)
{
	rotationVector[0] = x;
	rotationVector[1] = y;
	rotationVector[2] = z;

	rotationMatrix = glm::rotate(glm::mat4(1.0f), x, glm::vec3(1.0f, 0.0f, 0.0f));
	rotationMatrix *= glm::rotate(glm::mat4(1.0f), y, glm::vec3(0.0f, 1.0f, 0.0f));
	rotationMatrix *= glm::rotate(glm::mat4(1.0f), z, glm::vec3(0.0f, 0.0f, 1.0f));

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

	scaleMatrix = glm::scale(glm::mat4(1.0f), scaleVector);

	UpdateModel();
}

void Entity::SetScaleX(float x)
{
	scaleVector[0] = x;
	scaleMatrix = glm::scale(glm::mat4(1.0f), scaleVector);
	UpdateModel();
}

void Entity::SetScaleY(float y)
{
	scaleVector[1] = y;
	scaleMatrix = glm::scale(glm::mat4(1.0f), scaleVector);
	UpdateModel();
}

void Entity::SetScaleZ(float z)
{
	scaleVector[2] = z;
	scaleMatrix = glm::scale(glm::mat4(1.0f), scaleVector);
	UpdateModel();
}
void Entity::UpdateModel()
{
	model = translationMatrix * rotationMatrix * scaleMatrix;
}
vec3 Entity::GetTranslation()
{
	return translationVector;
}
float Entity::GetTranslationX()
{
	return translationVector[0];
}
float Entity::GetTranslationY()
{
	return translationVector[1];
}
float Entity::GetTranslationZ()
{
	return translationVector[2];
}
vec3 Entity::GetRotation()
{
	return rotationVector;
}
float Entity::GetRotationX()
{
	return rotationVector[0];
}
float Entity::GetRotationY()
{
	return rotationVector[1];
}
float Entity::GetRotationZ()
{
	return rotationVector[2];
}
vec3 Entity::GetScale()
{
	return scaleVector;
}
float Entity::GetScaleX()
{
	return scaleVector[0];
}
float Entity::GetScaleY()
{
	return scaleVector[1];
}
float Entity::GetScaleZ()
{
	return scaleVector[2];
}
void Entity::SetCollider(vec3 _position, float _height, float _width, Layers _layer, bool _isStatic)
{
	collider = new Collider(_position, _height, _width, _layer, _isStatic);

}

unsigned int Entity::GetColliderPivotX()
{
	return collider->GetXPosition();
}
unsigned int Entity::GetColliderPivotY()
{
	return collider->GetYPosition();
}
glm::vec2 Entity::GetColliderPivot()
{
	return collider->GetPivot();
}
unsigned int Entity::GetColliderHeight()
{
	return collider->GetHeight();
}
unsigned int Entity::GetColliderWidth()
{
	return collider->GetWidth();
}
Layers Entity::GetColliderLayer()
{
	return collider->GetLayer();
}
bool Entity::GetColliderIsStatic()
{
	return collider->GetIsStatic();
}





