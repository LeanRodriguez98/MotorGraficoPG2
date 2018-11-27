#pragma once
#include "Exports.h"
#include "Entity.h"
#include "Shape.h"
#include "Collider.h"
#include "CircleCollider.h"
#include "Definitions.h"
#include <vector>
#include <list>
using namespace std;

class  ENGINEDLL_API CollisionManager
{
private:
	static CollisionManager* instance;
	vector<list<Entity*>*> CollisionGroups;
	
public:
	CollisionManager();
	~CollisionManager();
	static CollisionManager* GetInstance();
	void AddCollisionEntity(Entity* e, Layers lyr);
	void CollisionDetector();
	void CheckCollisionsBetweenLayers(list<Entity*> *layerA, list<Entity*> *layerB);
	void CollisionBoxResolver(Entity* A, Entity* B);
};



