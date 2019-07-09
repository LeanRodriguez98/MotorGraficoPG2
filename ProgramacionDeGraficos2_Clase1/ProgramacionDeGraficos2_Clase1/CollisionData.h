#pragma once
#define LAYER_PLAYER 0
#define LAYER_CANNON 1
#define LAYER_BULLET 3
#define LAYER_GROUND 4
#define LAYER_LAND_PLATFORM 5
#define LAYER_DEAD_LIMIT 6
class CollisionData
{
public:
	CollisionData(int _CollisionLayer);
	~CollisionData();
	int CollisionLayer;
	bool isAlive = true;
	bool checkCollisionEvent = false;
};

