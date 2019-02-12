#include "Debug.h"
#include <windows.h>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <GLFW\glfw3.h>
#include <exception>
typedef std::basic_string<char> string;

Debug::Debug()
{
}

Debug::~Debug()
{
}

void Debug::Log(string text)
{
	//time
	std::ostringstream streamObj3;
	streamObj3 << std::fixed;
	streamObj3 << std::setprecision(1);
	streamObj3 << glfwGetTime();
	string time = "Time: " + streamObj3.str();

	//combine info to one line
	string finalString = "***" + time + " - " + text + "\n";

	//convert to cstring
	const char * output = finalString.c_str();

	//write to output window
	OutputDebugString(output);
}
void Debug::Log(int number)
{
	Log(std::to_string(number));
}
void Debug::Log(float number)
{
	Log(std::to_string(number));
}

void Debug::Error(string error, bool stopGame)
{
	Log("ERROR: " + error);
	if (stopGame || ALLWAYS_THROW)
		throw std::exception(error.c_str());
}
