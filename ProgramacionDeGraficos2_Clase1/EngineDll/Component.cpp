#include "Component.h"

Component::Component(Renderer * render) : Entity(render)
{
	type = ComponentsType::nullComponent;
}

void Component::Update(mat4 ViewMatrix)
{

}

void Component::Draw()
{
}


Component::~Component()
{
}