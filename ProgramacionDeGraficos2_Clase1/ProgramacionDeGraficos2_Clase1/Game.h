#include "../EngineDLL/Gamebase.h"
#include "../EngineDLL/Triangle.h"
#include "../EngineDLL/Square.h"
#include "../EngineDLL/Circle.h"
#include "../EngineDLL/Material.h"
#include "../EngineDLL/TextureImporter.h"
#include "../EngineDLL/Sprite.h"
#include "../EngineDll/Definitions.h"
#include "../EngineDll/CollisionManager.h"
#include <iostream>
class Game : public Gamebase {
private:
	int i;
	Triangle * triangle1;
	Square *square1;
	Circle   *circle1;
	Material * material1;
	Material * material2;
	Material * material3;
	Material * material4;
	Material * material5;
	Sprite  * sprite1;
	Sprite  * sprite2;
	Sprite  * sprite3;


public:
	Game();
	~Game();
protected:
	bool OnStart() override;
	bool OnStop() override;
	bool OnUpdate() override;
	void OnDraw() override;
};

