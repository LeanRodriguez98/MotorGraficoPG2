#include "Exports.h"
#include "Renderer.h"
#include "Window.h"
#include "TypeDefs.h"
#include <iostream>
#include "Time.h"
#include "Node.h"
using namespace std;
class ENGINEDLL_API Gamebase {
private:
	int screenHeight;
	int screenWidth;
public:
	Gamebase();
	~Gamebase();
	Window * window;
	Node * sceneNode;
	bool Start();
	bool Stop();
	void Loop();
	void SetScreenHeight(int _screenHeight);
	void SetScreenWidth(int _screenWidth);
	int GetScreenHeight();
	int GetScreenWidth();
	void SetSceneNode(Node * _sceneNode);
protected:
	Renderer * renderer;
	virtual bool OnStart() = 0;
	virtual bool OnStop() = 0;
	virtual bool OnUpdate() = 0;
	virtual void OnDraw() = 0;
};

