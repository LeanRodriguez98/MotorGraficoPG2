#include "../EngineDLL/Gamebase.h"
#include "../EngineDLL/Triangle.h"
#include "../EngineDLL/Square.h"
#include "../EngineDLL/Circle.h"
#include "../EngineDLL/Material.h"
#include "../EngineDLL/TextureImporter.h"
#include "../EngineDLL/Sprite.h"
#include "../EngineDll/Definitions.h"
#include "../EngineDll/ImputManager.h"
#include <Box2D/Box2D.h>

#include <iostream>
#include <vector>

#include "GroundChunk.h"
#include "Ship.h"
#include "Cannon.h"
#include "CollisionListener.h"
#include "CollisionData.h"
#include "DeadLimit.h"
#define PLAYER_SPEED 20.0f
#define SCREEN_WIDHT 10.5f

#define START_GENERATE_POSITION vec2(-10.0f, -3.0f)
#define GROUND_CHUNK_SIZE vec2(0.05f, 0.3f)
#define LAND_PLATFORM_SIZE vec2(0.8f, 0.3f)
#define VEC2_MINUS_X vec2(-1.0f,1.0f)
#define VEC2_MINUS_Y vec2(1.0f,-1.0f)

enum GameStates {mainMenu, game, gameOver, youWin};

class Game : public Gamebase {
private:
	
	b2World * gameWorld;
	vector<GroundChunk * > * terrain;
	vector<Cannon * > * cannons;
	vector<Bullet * > * bullets;
	Ship * ship;
	CollisionListener collisionListener;
	GameStates gameState;

	Material * mainMenuMaterial;
	Sprite * mainMenuSprite;

	Material * gameOverMaterial;
	Sprite * gameOverSprite;

	Material * youWinMaterial;
	Sprite * youWinSprite;

	DeadLimit * leftLimit;
	DeadLimit * rightLimit;
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

