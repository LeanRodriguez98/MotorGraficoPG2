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

enum ComponentsType {
	MeshRender = 0,
	CameraComponent,
	ColliderComponent,
	ScriptComponent,
	Transform,
	nullComponent
};