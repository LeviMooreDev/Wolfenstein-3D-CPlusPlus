#include "Time.h"
#include <GLFW\glfw3.h>

//declare static fields
float Time::deltaTime = 0;
float Time::oldTimeSinceStart = 0;

float Time::GetTimeSinceStart()
{
	return glfwGetTime();
}

float Time::GetDeltaTime()
{
	return deltaTime;
}

void Time::UpdateDeltaTime()
{
	deltaTime = GetTimeSinceStart() - oldTimeSinceStart;
	oldTimeSinceStart = GetTimeSinceStart();
}