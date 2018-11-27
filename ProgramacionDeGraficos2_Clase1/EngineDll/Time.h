#pragma once
#include "Exports.h"
static class ENGINEDLL_API Time
{
public:
	static double lastTime;
	static double time;
	static float dt;
	static double Measure();
	static void FirstMeasure();
	static double GetDT();
};

