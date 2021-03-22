#include "Debug.h"
#include <windows.h>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <GLFW\glfw3.h>
#include <exception>
typedef std::basic_string<char> string;

void Debug::Log(string value)
{
	//find time in seconds with a precision of 2 since the game started.
	std::ostringstream streamObj3;
	streamObj3 << std::fixed;
	streamObj3 << std::setprecision(1);
	streamObj3 << glfwGetTime();
	string time = "Time: " + streamObj3.str();

	//combine info into one line
	string finalString = "***" + time + " - " + value + "\n";

	//write to output window
	OutputDebugString(finalString.c_str());
}
void Debug::Log(int value)
{
	Log(std::to_string(value));
}
void Debug::Log(unsigned int value)
{
	Log(std::to_string(value));
}
void Debug::Log(float value)
{
	Log(std::to_string(value));
}

void Debug::Error(string error, bool stopGame)
{
	Log("ERROR: " + error);

	if (stopGame || ALLWAYS_THROW)
		throw std::exception(error.c_str());
}
