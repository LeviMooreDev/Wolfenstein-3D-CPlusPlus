#pragma once
#include "DLLHelper.h"
#include <iostream>
#include <string>
typedef std::basic_string<char> string;

//if true an ERROR() will allways throw an exception and stop the game
#define ALLWAYS_THROW false

//used to write debug messages to the visual studio output window
class DLLEXTERN Debug
{
public:
	//write string to visual studio output window
	static void Log(string text);
	//write int to visual studio output window
	static void Log(int number);
	//write unsigned int to visual studio output window
	static void Log(unsigned int number);
	//write float to visual studio output window
	static void Log(float number);
	//write error message to visual studio output window
	static void Error(string error, bool stopGame = false);
};

