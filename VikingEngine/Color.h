#pragma once
#include "DLLHelper.h"
#include <iostream>
#include <string>
typedef std::basic_string<char> string;

typedef unsigned char BYTE;

class DLLEXTERN Color
{
private:
	BYTE r = 0;
	BYTE b = 0;
	BYTE g = 0;
	BYTE a = 255;

public:
	Color();
	Color(BYTE color);
	Color(BYTE r, BYTE g, BYTE b);
	Color(BYTE r, BYTE g, BYTE b, BYTE a);
	Color(float color);
	Color(float r, float g, float b);
	Color(float r, float g, float b, float a);
	~Color();

	float R1();
	void R1(float value);
	BYTE R255();
	void R255(BYTE value);

	float G1();
	void G1(float value);
	BYTE G255();
	void G255(BYTE value);

	float B1();
	void B1(float value);
	BYTE B255();
	void B255(BYTE value);

	float A1();
	void A1(float value);
	BYTE A255();
	void A255(BYTE value);

	operator std::string() const;
};

