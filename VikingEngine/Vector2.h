#pragma once
#include "DLLHelper.h"
#include <iostream>

typedef std::basic_string<char> string;

//data type that can hold 2 floats and do vector math
class DLLEXTERN Vector2
{
public:
	float x = 0;
	float y = 0;

	Vector2() {};
	Vector2(float x, float y);

	//returns a vector(1, 1)
	static Vector2 One();
	//returns a vector(value, value)
	static Vector2 One(float value);

	//returns a vector(0, 1)
	static Vector2 Up();
	//returns a vector(0, value)
	static Vector2 Up(float value);

	//returns a vector(0, -1)
	static Vector2 Down();
	//returns a vector(0, -value)
	static Vector2 Down(float value);

	//returns a vector(1, 0)
	static Vector2 Right();
	//returns a vector(value, 0)
	static Vector2 Right(float value);

	//returns a vector(-1, 0)
	static Vector2 Left();
	//returns a vector(-value, 0)
	static Vector2 Left(float value);

	//move vector linearly towards target
	void MoveTowards(Vector2 target, float maxDistanceDelta);

	//returns next point in linearly interpolates to target
	Vector2 Lerp(Vector2 b, float t);

	//returns the distance to target
	float Distance(Vector2 target);

	//returns the squared length of this vector
	float SqrMagnitude();

	//returns the length of this vector
	float Magnitude();

	//returns this vector with a magnitude of 1
	Vector2 Normalized();

	//makes this vector have a magnitude of 1.
	void Normalize();

	bool operator==(const Vector2 & other) const;
	bool operator!=(const Vector2 & other) const;

	Vector2 operator+(const Vector2 & other);
	Vector2 operator-(const Vector2 & other);
	Vector2 operator*(const Vector2 & other);
	Vector2 operator/(const Vector2 & other);

	Vector2 operator+(const float & number);
	Vector2 operator-(const float & number);
	Vector2 operator*(const float & number);
	Vector2 operator/(const float & number);

	Vector2& operator+=(const Vector2 & other);
	Vector2& operator-=(const Vector2 & other);
	Vector2& operator*=(const Vector2 & other);
	Vector2& operator/=(const Vector2 & other);

	Vector2& operator+=(const float & number);
	Vector2& operator-=(const float & number);
	Vector2& operator*=(const float & number);
	Vector2& operator/=(const float & number);

	Vector2 operator!();

	operator std::string() const;
};

