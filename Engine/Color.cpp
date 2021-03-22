#include "Color.h"
#include <iostream>
#include <string>
typedef std::basic_string<char> string;


Color::Color(float color)
{
	r = g = b = color;
	a = 255;
}
Color::Color(float r, float g, float b)
{
	(*this).r = r;
	(*this).g = g;
	(*this).b = b;
	a = 255;
}
Color::Color(float r, float g, float b, float a)
{
	(*this).r = r;
	(*this).g = g;
	(*this).b = b;
	(*this).a = a;
}

Color::operator std::string() const
{
	return "(" + std::to_string(r) + ", " + std::to_string(g) + ", " + std::to_string(b) + ", " + std::to_string(a) + ")";
}