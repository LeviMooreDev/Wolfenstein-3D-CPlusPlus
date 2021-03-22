#pragma once
#include "DLLHelper.h"
#include <iostream>
#include <string>
typedef std::basic_string<char> string;

//data type that can hold a r,g,b,a value
class DLLEXTERN Color
{
public:
	float r = 0;
	float b = 0;
	float g = 0;
	float a = 255;

	Color() {};
	Color(float color);
	Color(float r, float g, float b);
	Color(float r, float g, float b, float a);

	operator std::string() const;
};

