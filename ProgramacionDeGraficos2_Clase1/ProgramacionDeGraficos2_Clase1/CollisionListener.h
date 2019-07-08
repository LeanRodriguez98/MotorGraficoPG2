#pragma once
#include <Box2D/Box2D.h>
#include "Ship.h"
#include "Bullet.h"
#include "Cannon.h"
#include "CollisionData.h"
class CollisionListener : public b2ContactListener
{
private:
	void CheckCollision(CollisionData &_collisionDataA, CollisionData &_collisionDataB);
public:
	void BeginContact(b2Contact* _contact);
};

 