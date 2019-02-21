#include "Exports.h"
#include "Renderer.h"
#include "Window.h"
#include "TypeDefs.h"
#include <iostream>
#include "Time.h"

using namespace std;
class ENGINEDLL_API Gamebase {
private:

	int screenHeight;
	int screenWidth;
public:
	Gamebase();
	~Gamebase();
	Window * window;

	bool Start();
	bool Stop();
	void Loop();
	void SetScreenHeight(int _screenHeight);
	void SetScreenWidth(int _screenWidth);
	int GetScreenHeight();
	int GetScreenWidth();
protected:
	Renderer * renderer;
	virtual bool OnStart() = 0;
	virtual bool OnStop() = 0;
	virtual bool OnUpdate() = 0;
	virtual void OnDraw() = 0;
};

