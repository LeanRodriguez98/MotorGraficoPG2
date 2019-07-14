#pragma once
#include "Exports.h"
#include "Component.h"
#include "Renderer.h"
#include <vector>
#include "../external/glm-0.9.9.0/glm/glm.hpp"
#include "../external/glm-0.9.9.0/glm/gtc/matrix_transform.hpp"
using namespace std;
using namespace glm;
class ENGINEDLL_API Node : public Entity
{
private:
	Renderer * renderer;
	vector<Component *> * components;
	vector<Node *> * nodes;
	mat4 viewMatrix;
	mat4 originalModelMatrix;
	mat4 originalViewMatrix;
	mat4 originalProjectionMatrix;
public:
	Node(Renderer * render);
	~Node();

	void Draw();
	void Update();
	void AddComponent(Component * _component);
	void RemoveComponentByIndex(int _index);
	void RemoveChildByIndex(int _index);
	void AddChild(Node * _node);
	Component * GetComponentByType(ComponentType _type);
	Component * GetComponentByIndex(int _index);
	Node * GetChildByIndex(int _index);
	vector<Node*>* GetChildsVector();
	vector<Component*>* GetComponentsVector();
};

         