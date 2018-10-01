#pragma once
#include "Exports.h"
#include <iostream>
using namespace std;
class ENGINEDLL_API Window
{
public:
	Window(int _whith, int _height, char * _windwName);
	~Window();
	bool start();
	bool stop();
	bool ShouldClose();
	void PollEvents();
	void * GetWindowPtr();
private:
	int whith;
	int height;
	const char * name;
	string windowName;
	void * window;
};

