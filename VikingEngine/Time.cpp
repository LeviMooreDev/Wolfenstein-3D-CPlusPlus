#include "Time.h"
#include <GLFW\glfw3.h>

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

void Time::Update()
{
	deltaTime = GetTimeSinceStart() - oldTimeSinceStart;
	oldTimeSinceStart = GetTimeSinceStart();
}