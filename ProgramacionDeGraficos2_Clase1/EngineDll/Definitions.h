#pragma once 

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