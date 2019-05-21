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

#include "Player.h"
#include "CollectableItem.h"
#include "StaticObject.h"
#include "mobileObject.h"
#include <iostream>


class Game : public Gamebase {
private:
	enum GameState 
	{
		MainMenu,
		InGame,
		GameOver 
	};


	Camera * camera;

	Mesh * mesh1;
	Material * materialMesh1;

	Mesh * mesh2;
	Material * materialMesh2;

public:
	Game();
	~Game();
protected:
	bool OnStart() override;
	bool OnStop() override;
	bool OnUpdate() override;
	void OnDraw() override;
};

