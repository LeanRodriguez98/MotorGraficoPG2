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
#include "../EngineDll/Camera.h"
#include "../EngineDll/Mesh.h"
#include "../EngineDll/MeshImporter.h"

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
	Camera * camera;
	GameState gamestate;

	Mesh * cube;
	Material * cubeMaterial;

public:
	Game();
	~Game();
protected:
	bool OnStart() override;
	bool OnStop() override;
	bool OnUpdate() override;
	void OnDraw() override;
};

