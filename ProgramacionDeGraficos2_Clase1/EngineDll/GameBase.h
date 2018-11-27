#include "Exports.h"
#include "Renderer.h"
#include "Window.h"
#include "TypeDefs.h"
#include <iostream>
#include "Time.h"

using namespace std;
class ENGINEDLL_API Gamebase {
private:

	Window * window;
public:
	Gamebase();
	~Gamebase();
	bool Start();
	bool Stop();
	void Loop();
protected:
	Renderer * renderer;
	virtual bool OnStart() = 0;
	virtual bool OnStop() = 0;
	virtual bool OnUpdate() = 0;
	virtual void OnDraw() = 0;
};

