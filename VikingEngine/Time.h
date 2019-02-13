#pragma once
#include "DLLHelper.h"

class Time
{
private:
	static float deltaTime;
	static float oldTimeSinceStart;

public:
	//returns the time passed since the game started in seconds
	DLLEXTERN static float GetTimeSinceStart();

	//returns delta time
	DLLEXTERN static float GetDeltaTime();

	//called by the engine
	static void Update();
};

