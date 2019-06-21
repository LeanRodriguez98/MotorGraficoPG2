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

#define START_GENERATE_POSITION vec2(-11.0f, -1.0f)
#define GROUND_CHUNK_SIZE vec2(0.05f, 0.1f)

#define VEC2_X2 vec2(2.0f,2.0f)
#define VEC2_X2_MINUS_Y vec2(2.0f,-2.0f)

#define SCREEN_WIDHT 10.5

class Game : public Gamebase {
private:
	

	Player * player1;
	b2World * gameWorld;

	vector<GroundChunk*> * terrain;
	Ship * ship;

public:
	Game();
	~Game();

	void GenerateTerrain();
	void UpdatePhisics();

protected:
	bool OnStart() override;
	bool OnStop() override;
	bool OnUpdate() override;
	void OnDraw() override;
};

