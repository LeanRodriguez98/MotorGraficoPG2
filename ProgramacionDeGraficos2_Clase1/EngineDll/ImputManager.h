#pragma once
#include "Exports.h"

class Window;

enum Key
{
	RightKey = 262,
	LeftKey = 263,
	DownKey = 264,
	UpKey = 265,
	SpaceKey = 32,
	EscapeKey = 256,
	EnterKey = 257,
	rightEnterKey = 335,
	TabKey = 258,
	AKey = 65,
	BKey = 66,
	CKey = 67,
	DKey = 68,
	EKey = 69,
	FKey = 70,
	GKey = 71,
	HKey = 72,
	IKey = 73,
	JKey = 74,
	KKey = 75,
	LKey = 76,
	MKey = 77,
	NKey = 78,
	OKey = 79,
	PKey = 80,
	QKey = 81,
	RKey = 82,
	SKey = 83,
	TKey = 84,
	UKey = 85,
	VKey = 86,
	WKey = 87,
	XKey = 88,
	YKey = 89,
	ZKey = 90,
	zeroKey = 48,
	oneKey = 49,
	twoKey = 50,
	threeKey = 51,
	fourKey = 52,
	fiveKey = 53,
	sixKey = 54,
	sevenKey = 55,
	eightKey = 56,
	nineKey = 57,
	rightZeroKey = 320,
	rightOneKey = 321,
	rightTwoKey = 322,
	rightThreeKey = 323,
	rightFourKey = 324,
	rightFiveKey = 325,
	rightSixKey = 326,
	rightSevenKey = 327,
	rightEightKey = 328,
	rightNineKey = 329
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

