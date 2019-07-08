#pragma once
#include <Box2D/Box2D.h>
#include "Ship.h"
#include "Bullet.h"
#include "Cannon.h"
class CollisionListener : public b2ContactListener
{
public:
	void BeginContact(b2Contact* _contact);
};

 