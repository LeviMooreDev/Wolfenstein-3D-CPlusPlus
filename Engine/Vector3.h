#pragma once
#include "DLLHelper.h"
#include <iostream>

typedef std::basic_string<char> string;

//data type that can hold 3 floats and do vector math
class DLLEXTERN Vector3
{
public:
	float x = 0;
	float y = 0;
	float z = 0;

	Vector3() { };
	Vector3(float x, float y, float z);

	//returns Vector3(1, 1, 1)
	static Vector3 One();
	//returns Vector3(value, value, value)
	static Vector3 One(float value);

	//returns Vector3(0, 1, 0)
	static Vector3 Up();
	//returns Vector3(0, value, 0)
	static Vector3 Up(float value);

	//returns Vector3(0, -1, 0)
	static Vector3 Down();
	//returns Vector3(0, -value, 0)
	static Vector3 Down(float value);

	//returns Vector3(1, 0, 0)
	static Vector3 Right();
	//returns Vector3(value, 0, 0)
	static Vector3 Right(float value);

	//returns Vector3(-1, 0, 0)
	static Vector3 Left();
	//returns Vector3(-value, 0, 0)
	static Vector3 Left(float value);

	//returns Vector3(0, 0, 1)
	static Vector3 Forward();
	//returns Vector3(0, 0, value)
	static Vector3 Forward(float value);

	//returns Vector3(0, 0, -1)
	static Vector3 Back();
	//returns Vector3(0, 0, -value)
	static Vector3 Back(float value);

	//move vector linearly towards target
	void MoveTowards(Vector3 target, float maxDistanceDelta);

	//returns next point in linearly interpolates to target
	Vector3 Lerp(Vector3 b, float t);

	//returns the distance to target
	float Distance(Vector3 target);

	//returns the angle in degrees between this and target
	float Angle(Vector3 target);

	//returns the squared length of this vector
	float SqrMagnitude();

	//returns the length of this vector
	float Magnitude();

	//returns this vector with a magnitude of 1
	Vector3 Normalized();

	//makes this vector have a magnitude of 1
	void Normalize();

	//returns cross product of two vectors
	static Vector3 Cross(Vector3 lhs, Vector3 rhs);

	//return dot product of two vectors
	static float Dot(Vector3 lhs, Vector3 rhs);

	//returns a copy of the vector rotated around an axis
	Vector3 Rotate(Vector3 axis, float degrees);


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

	//this is so we can access the vector using [] like in a array
	float& operator[] (int i);

	Vector3 operator!();

	operator std::string() const;
};

