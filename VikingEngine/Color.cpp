#include "Color.h"
#include <iostream>
#include <string>
typedef std::basic_string<char> string;


Color::Color()
{
}
Color::Color(BYTE color)
{
	r = g = b = color;
	a = 255;
}
Color::Color(BYTE r, BYTE g, BYTE b)
{
	(*this).r = r;
	(*this).g = g;
	(*this).b = b;
	a = 255;
}
Color::Color(BYTE r, BYTE g, BYTE b, BYTE a)
{
	(*this).r = r;
	(*this).g = g;
	(*this).b = b;
	(*this).a = a;
}
Color::Color(float color)
{
	r = g = b = a = (BYTE)(color * 255);
}
Color::Color(float r, float g, float b)
{
	(*this).r = (BYTE)(r * 255);
	(*this).g = (BYTE)(g * 255);
	(*this).b = (BYTE)(b * 255);
	a = 255;
}
Color::Color(float r, float g, float b, float a)
{
	(*this).r = (BYTE)(r * 255);
	(*this).g = (BYTE)(g * 255);
	(*this).b = (BYTE)(b * 255);
	(*this).a = (BYTE)(a * 255);
}
Color::~Color()
{
}

float Color::R1()
{
	return 1.0f / 255.0f * r;
}
void Color::R1(float value)
{
	r = (BYTE)(value * 255);
}
BYTE Color::R255()
{
	return r;
}
void Color::R255(BYTE value)
{
	r = value;
}

float Color::G1()
{
	return 1.0f / 255.0f * g;
}
void Color::G1(float value)
{
	g = (BYTE)(value * 255);
}
BYTE Color::G255()
{
	return g;
}
void Color::G255(BYTE value)
{
	g = value;
}

float Color::B1()
{
	return 1.0f / 255.0f * b;
}
void Color::B1(float value)
{
	b = (BYTE)(value * 255);
}
BYTE Color::B255()
{
	return b;
}
void Color::B255(BYTE value)
{
	b = value;
}

float Color::A1()
{
	return 1.0f / 255.0f * a;
}
void Color::A1(float value)
{
	a = (BYTE)(value * 255);
}
BYTE Color::A255()
{
	return a;
}
void Color::A255(BYTE value)
{
	a = value;
}

Color::operator std::string() const
{
	return "(" + std::to_string(r) + ", " + std::to_string(g) + ", " + std::to_string(b) + ", " + std::to_string(a) + ")";
}