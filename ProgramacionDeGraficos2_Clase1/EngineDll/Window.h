
#pragma once
#include "Exports.h"
#include <iostream>
using namespace std;
class ENGINEDLL_API Window
{
private:
	void* window;
	int width;
	int height;
	const char* name;
public:
	Window();
	~Window();
	bool Start(int w, int h, const char* n);
	bool Stop();
	bool ShouldClose();
	void PollEvents();
	void* GetWindow();
};


