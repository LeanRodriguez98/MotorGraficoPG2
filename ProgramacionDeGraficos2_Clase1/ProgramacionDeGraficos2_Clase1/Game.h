#include "../EngineDLL/Gamebase.h"
#include "../EngineDLL/Triangle.h"
#include "../EngineDLL/Square.h"
#include "../EngineDLL/Circle.h"
#include "../EngineDLL/Material.h"
#include "../EngineDLL/TextureImporter.h"
#include "../EngineDLL/Sprite.h"
#include "../EngineDll/Definitions.h"
#include "../EngineDll/CollisionManager.h"
#include "../EngineDll/Tilemap.h"
#include "../EngineDll/ImputManager.h"
#include <Box2D/Box2D.h>

#include "Player.h"
#include <iostream>

#include "GroundChunk.h"
#include "Ship.h"
#define PLAYER_SPEED 20.0f

class Game : public Gamebase {
private:
	

	Player * player1;
	vector<Square*> * terrain;



	b2World * gameWorld;
	
	GroundChunk * groundChunk;
	Ship * ship;

public:
	Game();
	~Game();
protected:
	bool OnStart() override;
	bool OnStop() override;
	bool OnUpdate() override;
	void OnDraw() override;
};

