#pragma once
#include "Exports.h"
class ENGINEDLL_API Camara
{
private:

public:
	Camara();
	~Camara();
	void CameraWalk(float _directionMatrix);
	void CameraStrafe(float _directionMatrix);
};

