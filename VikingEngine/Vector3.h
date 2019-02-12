#pragma once
#include "DLLHelper.h"
#include <iostream>

typedef std::basic_string<char> string;

class DLLEXTERN Vector3
{
public:
	enum Pivot
	{
		X,Y,Z
	};

	float x = 0;
	float y = 0;
	float z = 0;

	Vector3();
	Vector3(float x, float y, float z);
	~Vector3();

	//returns Vector3(1,1,1)
	static Vector3 One();
	//returns Vector3(0,1,0)
	static Vector3 Up();
	//returns Vector3(0,-1,0)
	static Vector3 Down();
	//returns Vector3(1,0,0)
	static Vector3 Right();
	//returns Vector3(-1,0,0)
	static Vector3 Left();
	//returns Vector3(0,0,1)
	static Vector3 Forward();
	//returns Vector3(0,0,-1)
	static Vector3 Back();

	//move linearly towards target
	void MoveTowards(Vector3 target, float maxDistanceDelta);

	//returns next point in linearly interpolates to target
	Vector3 Lerp(Vector3 b, float t);

	//returns the distance to target
	float Distance(Vector3 target);

	//returns the squared length of this vector
	float SqrMagnitude();
	//returns the length of this vector
	float Magnitude();

	//returns this vector with a magnitude of 1
	Vector3 Normalized();
	//makes this vector have a magnitude of 1.
	void Normalize();

	bool operator==(const Vector3 & other) const;
	bool operator!=(const Vector3 & other) const;

	Vector3 operator+(const Vector3 & other);
	Vector3 operator-(const Vector3 & other);
	Vector3 operator*(const Vector3 & other);
	Vector3 operator/(const Vector3 & other);

	Vector3 operator+(const float & number);
	Vector3 operator-(const float & number);
	Vector3 operator*(const float & number);
	Vector3 operator/(const float & number);

	Vector3& operator+=(const Vector3 & other);
	Vector3& operator-=(const Vector3 & other);
	Vector3& operator*=(const Vector3 & other);
	Vector3& operator/=(const Vector3 & other);

	Vector3& operator+=(const float & number);
	Vector3& operator-=(const float & number);
	Vector3& operator*=(const float & number);
	Vector3& operator/=(const float & number);

	Vector3 operator!();

	operator std::string() const;
};

