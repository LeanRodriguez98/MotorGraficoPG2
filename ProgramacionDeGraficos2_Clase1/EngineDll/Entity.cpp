#include "Entity.h"

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

	translationMatrix = translate(mat4(1.0f), translationVector);

	UpdateModel();
}


void Entity::SetTranslationX(float x)
{
	translationVector[0] = x;
	translationMatrix = translate(mat4(1.0f), translationVector);
	UpdateModel();
}

void Entity::SetTranslationY(float y)
{
	translationVector[1] = y;
	translationMatrix = translate(mat4(1.0f), translationVector);
	UpdateModel();
}

void Entity::SetTranslationZ(float z)
{
	translationVector[2] = z;
	translationMatrix = translate(mat4(1.0f), translationVector);
	UpdateModel();
}



void Entity::SetRotation(float x, float y, float z)
{
	rotationVector[0] = x;
	rotationVector[1] = y;
	rotationVector[2] = z;

	rotationMatrix = rotate(mat4(1.0f), x, vec3(1.0f, 0.0f, 0.0f));
	rotationMatrix *= rotate(mat4(1.0f), y, vec3(0.0f, 1.0f, 0.0f));
	rotationMatrix *= rotate(mat4(1.0f), z, vec3(0.0f, 0.0f, 1.0f));

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


void Entity::SetRotationMatrix(float x, float y, float z, float w)
{
	float pitch, yaw, roll;

	vec4 quaternion = normalize(vec4(x, y, z, w));

	ConvertToEulerAngles(quaternion, pitch, yaw, roll);

	rotationVector = vec3(pitch, yaw, roll);

	mat4 mat1 = mat4
	{
		quaternion.w, quaternion.z, -quaternion.y, quaternion.x,
		-quaternion.z, quaternion.w, quaternion.x, quaternion.y,
		quaternion.y, -quaternion.x, quaternion.w, quaternion.z,
		-quaternion.x, -quaternion.y, -quaternion.z, quaternion.w
	};

	mat4 mat2 = mat4
	{
		quaternion.w, quaternion.z, -quaternion.y, -quaternion.x,
		-quaternion.z, quaternion.w, quaternion.x, -quaternion.y,
		quaternion.y, -quaternion.x, quaternion.w, -quaternion.z,
		quaternion.x, quaternion.y, quaternion.z, quaternion.w
	};

	rotationMatrix = mat1 * mat2;

	ClampEulerRotation();
	UpdateModel();
}

void Entity::ConvertToEulerAngles(const vec4 quaternion, float& pitch, float& yaw, float& roll)
{
	float sinPitchCosYaw = 2.0f * (quaternion.w * quaternion.x + quaternion.y * quaternion.z);
	float cosPitchCosYaw = 1.0f - 2.0f * (quaternion.x * quaternion.x + quaternion.y * quaternion.y);
	pitch = atan(sinPitchCosYaw, cosPitchCosYaw);

	float sinYaw = 2.0f * (quaternion.w * quaternion.y - quaternion.z * quaternion.x);
	yaw = (abs(sinYaw) >= 1.0f) ? sign(sinYaw) * half_pi<float>() : asin(sinYaw);

	float sinRollCosYaw = 2.0f * (quaternion.w * quaternion.z + quaternion.x * quaternion.y);
	float cosRollCosYaw = 1.0f - 2.0f * (quaternion.y * quaternion.y + quaternion.z * quaternion.z);
	roll = atan(sinRollCosYaw, cosRollCosYaw);

	pitch = degrees(pitch);
	yaw = degrees(yaw);
	roll = degrees(roll);
}

void Entity::ClampEulerRotation()
{
	if (rotationVector.x < 0.0f || rotationVector.x >= 360.0f)
		rotationVector.x = rotationVector.x - (floor(rotationVector.x / 360.0f) * 360.0f);

	if (rotationVector.y < 0.0f || rotationVector.y >= 360.0f)
		rotationVector.y = rotationVector.y - (floor(rotationVector.y / 360.0f) * 360.0f);

	if (rotationVector.z < 0.0f || rotationVector.z >= 360.0f)
		rotationVector.z = rotationVector.z - (floor(rotationVector.z / 360.0f) * 360.0f);
}

void Entity::SetScale(float x, float y, float z)
{
	scaleVector[0] = x;
	scaleVector[1] = y;
	scaleVector[2] = z;

	scaleMatrix = scale(mat4(1.0f), scaleVector);

	UpdateModel();
}

void Entity::SetScaleX(float x)
{
	scaleVector[0] = x;
	scaleMatrix = scale(mat4(1.0f), scaleVector);
	UpdateModel();
}

void Entity::SetScaleY(float y)
{
	scaleVector[1] = y;
	scaleMatrix = scale(mat4(1.0f), scaleVector);
	UpdateModel();
}

void Entity::SetScaleZ(float z)
{
	scaleVector[2] = z;
	scaleMatrix = scale(mat4(1.0f), scaleVector);
	UpdateModel();
}
void Entity::UpdateModel()
{
	model = translationMatrix * rotationMatrix * scaleMatrix;
}

mat4 Entity::GetRotationMatrix()
{
	return rotationMatrix;
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
vec2 Entity::GetColliderPivot()
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





