#pragma once 
#define CANT_BOUNDING_BOX_VERTEX 8

enum  Layers
{
	player,
	enemy,
	walkeable,
	not_walkeable,
	tiles,
	count
};

enum ComponentType 
{
	MeshRendererComponent = 0,
	CameraComponent,
	NullComponent,
	Count
};

enum Planes {
	TOP = 0,
	BOTTOM, 
	LEFT,
	RIGHT,
	NEARP,
	FARP, 
	COUNT
};