#pragma once
#include "DLLHelper.h"

//use to keep track of time in our game
class Time
{
private:
	//the time in seconds since the last frame
	static float deltaTime;

	//the time in seconds since the game started last frame
	static float oldTimeSinceStart;

public:
	//returns the time in seconds since the last frame
	DLLEXTERN static float GetDeltaTime();

	//returns the time passed since the game started in seconds
	DLLEXTERN static float GetTimeSinceStart();

	//update the delta time update, called by the engine 
	static void UpdateDeltaTime();
};

