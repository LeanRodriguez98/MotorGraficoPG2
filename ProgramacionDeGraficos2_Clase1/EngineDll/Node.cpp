#include "Node.h"


Node::Node(Renderer * _renderer) : Entity(_renderer)
{
	renderer = _renderer;
	model = _renderer->GetModelMatrix();
	nodes = new vector<Node *>();
	components = new vector<Component *>();
}


Node::~Node()
{
}

void Node::AddComponent(Component * _component)
{
	components->push_back(_component);
}

Component * Node::GetComponentByType(ComponentType _type)
{
	for (size_t i = 0; i < components->size(); i++)
	{
		if (components->at(i)->type == _type)
			return components->at(i);
	}
	return nullptr;
}



void Node::RemoveComponentByIndex(int _index)
{
	int i = 0;
	for (vector<Component*>::iterator it = components->begin(); it != components->end(); ++it)
	{
		i++;
		if (i == _index)
		{
			components->erase(it);
			break;
		}
	}
}

void Node::RemoveChildByIndex(int _index)
{
	int i = 0;
	for (vector<Node*>::iterator it = nodes->begin(); it != nodes->end(); ++it)
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

vector<Node*>* Node::GetChildsVector() {
	if (nodes == nullptr || nodes->size() == 0)
	{
		return nullptr;
	}
	return nodes;
}

vector<Component*>* Node::GetComponentsVector()
{
	if (components == nullptr || components->size() == 0)
	{
		return nullptr;
	}
	return components;
}

Node * Node::GetChildByIndex(int _index)
{
	if (nodes->size() == 0)
	{
		return nullptr;
	}

	if (_index > nodes->size())
	{
		return nodes->at(nodes->size() - 1);
	}
	return nodes->at(_index);
}

Component * Node::GetComponentByIndex(int _index) {

	if (components->size() == 0)
	{
		return nullptr;
	}

	if (_index > components->size())
	{
		return components->at(components->size() - 1);
	}
	return components->at(_index);
}

void Node::Update()
{
	for (int i = 0; i < components->size(); i++)
	{
		components->at(i)->Update();
	}

	for (int i = 0; i < nodes->size(); i++)
	{
		nodes->at(i)->Update();
	}
}

void Node::Draw()
{

	originalModelMatrix = renderer->GetModelMatrix();
	originalViewMatrix = renderer->GetViewMatrix();
	originalProjectionMatrix = renderer->GetProjectionMatrix();
	renderer->MultiplyWorldMatrix(originalModelMatrix * model);

	for (int i = 0; i < components->size(); i++)
	{
		components->at(i)->Draw();
	}

	for (int i = 0; i < nodes->size(); i++)
	{
		nodes->at(i)->Draw();
	}

	renderer->SetViewMatrix(viewMatrix);
	renderer->SetViewMatrix(originalViewMatrix);
	renderer->SetModelMatrix(originalModelMatrix);
	renderer->SetProjectionMatrix(originalProjectionMatrix);
}

