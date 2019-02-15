#pragma once
#include "DLLHelper.h"
#include <iostream>

typedef std::basic_string<char> string;

class DLLEXTERN Vector2
{
public:
	float x = 0;
	float y = 0;

	Vector2();
	Vector2(float x, float y);
	~Vector2();

	static Vector2 One();
	static Vector2 One(float value);
	static Vector2 Up();
	static Vector2 Up(float value);
	static Vector2 Down();
	static Vector2 Down(float value);
	static Vector2 Right();
	static Vector2 Right(float value);
	static Vector2 Left();
	static Vector2 Left(float value);

	//move linearly towards target
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

