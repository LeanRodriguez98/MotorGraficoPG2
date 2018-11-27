#pragma once
#include "Exports.h"
class ENGINEDLL_API Animation
{
private:
	int actualFrame;
	int cantFrames;
	float frameWidth;
	float timer;
	float frameTimer;
	float * frame;

public:
	Animation(float _cantFrames);
	~Animation();
	float * UpdateFrame();
};

