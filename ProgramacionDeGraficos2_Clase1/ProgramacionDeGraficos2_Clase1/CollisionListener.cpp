#include "CollisionListener.h"



void CollisionListener::BeginContact(b2Contact* _contact)
{
	CollisionData * contact1 = (CollisionData *)_contact->GetFixtureA()->GetBody()->GetUserData();
	CollisionData * contact2 = (CollisionData *)_contact->GetFixtureB()->GetBody()->GetUserData();

	if (contact1)
	{
		if (contact2)
		{
			CheckCollision(*contact1, *contact2);
			CheckCollision(*contact2, *contact1);
		}
	}
}


void CollisionListener::CheckCollision(CollisionData &_collisionDataA, CollisionData &_collisionDataB) 
{
	switch (_collisionDataA.CollisionLayer)
	{

	case LAYER_PLAYER:
		
		switch (_collisionDataB.CollisionLayer)
		{
		case LAYER_BULLET:
			_collisionDataB.isAlive = false;
			break;
		default:
			break;
		}
		break;

	case LAYER_GROUND:

		switch (_collisionDataB.CollisionLayer)
		{
		case LAYER_BULLET:
			_collisionDataB.isAlive = false;
			break;
		case LAYER_PLAYER:
			_collisionDataB.isAlive = false;
			break;
		default:
			break;
		}
		break;

	case LAYER_CANNON:

		switch (_collisionDataB.CollisionLayer)
		{
		case LAYER_PLAYER:
			_collisionDataB.isAlive = false;
			break;
		default:
			break;
		}
		break;

	case LAYER_BULLET:

		switch (_collisionDataB.CollisionLayer)
		{
		case LAYER_PLAYER:
			_collisionDataB.isAlive = false;
			break;
		default:
			break;
		}
		break;

	case LAYER_LAND_PLATFORM:

		switch (_collisionDataB.CollisionLayer)
		{
		case LAYER_PLAYER:
			_collisionDataB.checkCollisionEvent = true;
			break;
		case LAYER_BULLET:
			_collisionDataB.isAlive = false;
			break;
		default:
			break;
		}
		break;

	case LAYER_DEAD_LIMIT:

		switch (_collisionDataB.CollisionLayer)
		{
		case LAYER_PLAYER:
			_collisionDataB.isAlive = false;
			break;
		case LAYER_BULLET:
			_collisionDataB.isAlive = false;
			break;
		default:
			break;
		}
		break;

	default:
		break;
	}
}

