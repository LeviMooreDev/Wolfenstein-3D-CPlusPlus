#pragma once
#include "DLLHelper.h"
#include <iostream>
#include <string>
typedef std::basic_string<char> string;

//if true an ERROR() will allways throw an exception and stop the game
#define ALLWAYS_THROW false

class DLLEXTERN Debug
{
public:
	Debug();
	~Debug();

	//write string to visual studio output window
	static void Log(string text);
	//write int to visual studio output window
	static void Log(int number);
	//write error message to visual studio output window
	static void Error(string error, bool stopGame = false);
};

