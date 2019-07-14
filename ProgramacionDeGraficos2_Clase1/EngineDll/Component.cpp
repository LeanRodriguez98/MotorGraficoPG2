#include "Component.h"

Component::Component(Renderer * render) : Entity(render)
{
	type = ComponentType::NullComponent;
}

void Component::Update()
{

}

void Component::Draw()
{
}


Component::~Component()
{
}