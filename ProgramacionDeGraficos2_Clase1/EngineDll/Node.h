#pragma once
#include "Exports.h"
#include "Component.h"
#include "Renderer.h"
#include <list>
#include<glm/glm.hpp>
#include<glm\gtc\matrix_transform.hpp>
using namespace std;
using namespace glm;
class ENGINEDLL_API Node
{
private:
	Renderer * render;

	list<Component *> * components;
	list<Node *> * nodes;
	mat4 viewMatrix;

public:
	Node(Renderer * render);
	~Node();

	void AddComponent(Component * _component);
	void RemoveComponent(int _index);
	Component * GetComponent(ComponentsType _type);
	void RemoveChild(int _index);
	void AddChild(Node * _node);
	void Update(mat4 ViewMatrix, int i);
	void Draw();
};

         