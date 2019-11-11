#include "Collider.h"



Collider::Collider(vec2 _pivotPosition, float _height, float _width, Layers _layer, bool _isStatic)
{
	pivotPosition = _pivotPosition;
	height = _height;
	width = _width;
	layer = _layer;
	isStatic = _isStatic;
}


Collider::~Collider()
{
}

unsigned int Collider::GetXPosition()
{
	return pivotPosition.x;
}
unsigned int Collider::GetYPosition()
{
	return pivotPosition.y;
}
vec2 Collider::GetPivot()
{
	return pivotPosition;
}
unsigned int Collider::GetHeight()
{
	return height;
}
unsigned int Collider::GetWidth()
{
	return width;
}

Layers Collider::GetLayer() 
{
	return layer;
}

bool Collider::GetIsStatic() 
{
	return isStatic;
}