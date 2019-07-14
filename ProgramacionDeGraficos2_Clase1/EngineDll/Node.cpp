#include "Node.h"


Node::Node(Renderer * _renderer)
{
	render = _renderer;
	nodes = new list<Node *>();
	components = new list<Component *>();
}


Node::~Node()
{
}

void Node::AddComponent(Component * _component)
{
	components->push_back(_component);
}

Component * Node::GetComponent(ComponentsType _type)
{
	for (std::list<Component*>::iterator it = components->begin(); it != components->end(); ++it)
	{
		if ((*it)->type == _type)
			return (*it);
	}
	return new Component(render);
}

void Node::RemoveComponent(int _index)
{
	int i = 0;
	for (std::list<Component*>::iterator it = components->begin(); it != components->end(); ++it)
	{
		i++;
		if (i == _index)
		{
			components->erase(it);
			break;
		}
	}
}

void Node::RemoveChild(int _index)
{
	int i = 0;
	for (std::list<Node*>::iterator it = nodes->begin(); it != nodes->end(); ++it)
	{
		i++;
		if (i == _index)
		{
			nodes->erase(it);
			break;
		}
	}
}

void Node::AddChild(Node * _node)
{
	nodes->push_back(_node);
}

void Node::Update(mat4 vMatrix, int i)
{
	viewMatrix *= render->GetViewMatrix();
	for (std::list<Component*>::iterator it = components->begin(); it != components->end(); ++it)
	{
		(*it)->Update(viewMatrix);
	}

	for (std::list<Node*>::iterator it = nodes->begin(); it != nodes->end(); ++it)
	{
		(*it)->Update(render->GetViewMatrix(), i + 1);
	}

	render->SetViewMatrix(viewMatrix);
}

void Node::Draw()
{
	for (std::list<Component*>::iterator it = components->begin(); it != components->end(); ++it)
	{
		(*it)->Draw();
	}
	for (std::list<Node*>::iterator it = nodes->begin(); it != nodes->end(); ++it)
	{
		(*it)->Draw();
	}
}
