#pragma once
class CollisionData
{
public:
	CollisionData(int _CollisionLayer);
	~CollisionData();
	int CollisionLayer;
	bool isAlive = true;
};

