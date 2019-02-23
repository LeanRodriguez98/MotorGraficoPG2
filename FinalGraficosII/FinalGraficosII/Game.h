#include "../EngineDLL/Include/GameBase.h"
#include "../EngineDLL/Include/Triangle.h"
#include "../EngineDLL/Include/Square.h"
#include "../EngineDLL/Include/Circle.h"
#include "../EngineDLL/Include/Material.h"
#include "../EngineDLL/Include/TextureImporter.h"
#include "../EngineDLL/Include/Sprite.h"
#include "../EngineDll/Include/Definitions.h"
#include "../EngineDll/Include/CollisionManager.h"
#include "../EngineDll/Include/Tilemap.h"
#include "../EngineDll/Include/ImputManager.h"

#include "Player.h"
#include "CollectableItem.h"
#include "StaticObject.h"
#include "mobileObject.h"
#include <iostream>

#define PLAYER_SPEED 20.0f

class Game : public Gamebase {
private:
	enum GameState 
	{
		MainMenu,
		InGame,
		GameOver
	};

	Material * materialTilemap1;
	Tilemap * tilemap1;
	Player * player1;
	vector<CollectableItem*> * bones;
	vector<StaticObject*> * trees;
	vector<MobileObject*> * rocks;
	Material * mainMenuMaterial;
	Material * gameOverMaterial;
	Sprite * mainMenuSprite;
	Sprite * gameOverSprite;
	GameState gamestate;
public:
	Game();
	~Game();
protected:
	bool OnStart() override;
	bool OnStop() override;
	bool OnUpdate() override;
	void OnDraw() override;
};

