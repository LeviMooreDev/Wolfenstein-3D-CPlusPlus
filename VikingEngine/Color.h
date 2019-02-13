#pragma once
#include "DLLHelper.h"

typedef unsigned char BYTE;

class Color
{
private:
	BYTE r = 0;
	BYTE b = 0;
	BYTE g = 0;
	BYTE a = 255;

public:
	DLLEXTERN Color();
	DLLEXTERN Color(BYTE color);
	DLLEXTERN Color(BYTE r, BYTE g, BYTE b);
	DLLEXTERN Color(BYTE r, BYTE g, BYTE b, BYTE a);
	DLLEXTERN Color(float color);
	DLLEXTERN Color(float r, float g, float b);
	DLLEXTERN Color(float r, float g, float b, float a);
	DLLEXTERN ~Color();

	DLLEXTERN float R1();
	DLLEXTERN void R1(float value);
	DLLEXTERN BYTE R255();
	DLLEXTERN void R255(BYTE value);

	DLLEXTERN float G1();
	DLLEXTERN void G1(float value);
	DLLEXTERN BYTE G255();
	DLLEXTERN void G255(BYTE value);

	DLLEXTERN float B1();
	DLLEXTERN void B1(float value);
	DLLEXTERN BYTE B255();
	DLLEXTERN void B255(BYTE value);

	DLLEXTERN float A1();
	DLLEXTERN void A1(float value);
	DLLEXTERN BYTE A255();
	DLLEXTERN void A255(BYTE value);
};

