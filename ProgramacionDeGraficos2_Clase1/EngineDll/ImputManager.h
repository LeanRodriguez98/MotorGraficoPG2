#pragma once
#include "Exports.h"

class Window;

enum Key
{
	RightKey = 262,
	LeftKey = 263,
	DownKey = 264,
	UpKey = 265
};


class ENGINEDLL_API ImputManager
{
private:
	static ImputManager* instance;
	Window* window;

	ImputManager();
	~ImputManager();
public:
	static ImputManager* GetInstance();
	
	void SetWindow(Window* _window);
	bool GetKeyDown(Key _key);
};

