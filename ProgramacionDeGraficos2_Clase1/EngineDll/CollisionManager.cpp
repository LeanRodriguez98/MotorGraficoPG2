#include "CollisionManager.h"



CollisionManager::CollisionManager()
{
	for (int i = 0; i < (int)Layers::count; i++)
	{
		CollisionGroups.push_back(new list<Entity*>());
	}
}


CollisionManager::~CollisionManager()
{
}
CollisionManager* CollisionManager::instance = 0;
CollisionManager* CollisionManager::GetInstance()
{
	if (instance == 0)
	{
		instance = new CollisionManager();
	}
	return instance;
}

void CollisionManager::AddCollisionEntity(Entity* e, Layers lyr)
{

	CollisionGroups[lyr]->push_back(e);
}

void CollisionManager::CollisionDetector()
{
	for (int i = 0; i < (int)Layers::count; i++)
	{
		for (int j = i + 1; j < (int)Layers::count; j++)
		{
			CheckCollisionsBetweenLayers(CollisionGroups[i], CollisionGroups[j]);
		}
	}
}

void CollisionManager::CheckCollisionsBetweenLayers(list<Entity*> *layerA, list<Entity*> *layerB)
{

	for (list<Entity*>::iterator i = layerA->begin(); i != layerA->end(); ++i) 
	{
		for (list<Entity*>::iterator j = layerB->begin(); j != layerB->end(); ++j) 
		{
			CollisionBoxResolver(*i, *j);
		}
	}

}

void CollisionManager::CollisionBoxResolver(Entity* A, Entity* B) 
{

	vec2 translateA = vec2(A->GetTranslationX(), A->GetTranslationY());
	vec2 translateB = vec2(B->GetTranslationX(),B->GetTranslationY());
	vec2 module = abs((translateA +  A->GetColliderPivot()) -( translateB + B->GetColliderPivot()));
	
	if (module.x < (A->GetColliderWidth() + B->GetColliderWidth()) / 2.0f && module.y < (A->GetColliderHeight() + B->GetColliderHeight()) / 2.0f)
	{

		float penetrationX = ((A->GetColliderWidth() / 2.0f) + (B->GetColliderWidth() / 2.0f)) - module.x;
		float penetrationY = ((A->GetColliderHeight() / 2.0f) + (B->GetColliderHeight() / 2.0f)) - module.y;

		if (penetrationX > penetrationY)
		{
			float factor = 1;
			if (A->GetTranslationY() < B->GetTranslationY())
			{
				factor = -1;
			}
			if (A->GetColliderIsStatic())
			{
				B->SetTranslation(B->GetTranslationX(), B->GetTranslationY() - (penetrationY * factor), 0.0f);
			}
			else if (B->GetColliderIsStatic())
			{
				A->SetTranslation(A->GetTranslationX(), A->GetTranslationY() + (penetrationY * factor), 0.0f);
			}
			else
			{
				A->SetTranslation(A->GetTranslationX(), A->GetTranslationY() - ((penetrationY / 2.0f) * factor), 0.0f);
				B->SetTranslation(B->GetTranslationX(), B->GetTranslationY() + ((penetrationY / 2.0f) * factor), 0.0f);
			}
	
	
		}
		else
		{

			float factor = 1;
			if (A->GetTranslationX() < B->GetTranslationX())
			{
				factor = -1;
			}


			if (A->GetColliderIsStatic())
			{
				B->SetTranslation(B->GetTranslationX() - (penetrationX * factor), B->GetTranslationY(), 0.0f);
			}
			else if (B->GetColliderIsStatic())
			{
				A->SetTranslation(A->GetTranslationX() + (penetrationX * factor), A->GetTranslationY(), 0.0f);
			}
			else
			{
				A->SetTranslation(A->GetTranslationX() + ((penetrationX / 2.0f) * factor), A->GetTranslationY(), 0.0f);
				B->SetTranslation(B->GetTranslationX() - ((penetrationX / 2.0f) * factor), B->GetTranslationY(), 0.0f);
	
			}
		}
	}



}