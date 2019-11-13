#include "BoundingBox3D.h"

vec3 BoundingBox3D::GetVertex(int _index)
{
	vec4 globalRotatedPos(boundingBox3D[_index].x, boundingBox3D[_index].y, boundingBox3D[_index].z, 1.0f);

	globalRotatedPos = renderer->GetModelMatrix() * globalRotatedPos;

	return (vec3)globalRotatedPos;
}

void BoundingBox3D::SetVertex(vec3 _boundingBox3D[CANT_BOUNDING_BOX_VERTEX])
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

void BoundingBox3D::SetWireCubeVertex(WhireCube * _wireCube) 
{
	float * vertex = new float[CANT_BOUNDING_BOX_VERTEX * 3]
	{
		boundingBox3D[0].x, boundingBox3D[0].y, boundingBox3D[0].z,
		boundingBox3D[1].x, boundingBox3D[1].y, boundingBox3D[1].z,
		boundingBox3D[2].x, boundingBox3D[2].y, boundingBox3D[2].z,
		boundingBox3D[3].x, boundingBox3D[3].y, boundingBox3D[3].z,
		boundingBox3D[4].x, boundingBox3D[4].y, boundingBox3D[4].z,
		boundingBox3D[5].x, boundingBox3D[5].y, boundingBox3D[5].z,
		boundingBox3D[6].x, boundingBox3D[6].y, boundingBox3D[6].z,
		boundingBox3D[7].x, boundingBox3D[7].y, boundingBox3D[7].z,
	};
	_wireCube->SetVertexBuffer(vertex, CANT_BOUNDING_BOX_VERTEX * 3);
}

