#include "BoundingBox3D.h"

vec3 BoundingBox3D::GetVertex(int _index)
{
	vec4 globalRotatedPos(boundingBox3D[_index].x, boundingBox3D[_index].y, boundingBox3D[_index].z, 1.0f);

	globalRotatedPos = renderer->GetModelViewProjectionMatrix() * globalRotatedPos;

	return (vec3)globalRotatedPos;
}

void BoundingBox3D::SetVertex(glm::vec3 _boundingBox3D[CANT_BOUNDING_BOX_VERTEX])
{
	for (int i = 0; i < CANT_BOUNDING_BOX_VERTEX; i++)
	{
		boundingBox3D[i] = _boundingBox3D[i];
	}
	loaded = true;
}

BoundingBox3D::BoundingBox3D(Renderer * _renderer)
{
	renderer = _renderer;
	for (int i = 0; i < CANT_BOUNDING_BOX_VERTEX; i++)
	{
		boundingBox3D[i] = vec3(0.0f,0.0f,0.0f);
	}
	loaded = false;
}


