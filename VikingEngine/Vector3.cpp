#include <algorithm>
#include <iostream>
#include <string>
#include "Vector3.h"
#include "Debug.h"
typedef std::basic_string<char> string;

Vector3::Vector3()
{
}
Vector3::Vector3(float x, float y, float z)
{
	(*this).x = x;
	(*this).y = y;
	(*this).z = z;
}
Vector3::~Vector3()
{
}

Vector3 Vector3::One()
{
	return Vector3(1, 1, 1);
}
Vector3 Vector3::One(float value)
{
	return One() * value;
}
Vector3 Vector3::Up()
{
	return Vector3(0, -1, 0);
}
Vector3 Vector3::Up(float value)
{
	return Up() * value;
}
Vector3 Vector3::Down()
{
	return Vector3(0, 1, 0);
}
Vector3 Vector3::Down(float value)
{
	return Down() * value;
}
Vector3 Vector3::Right()
{
	return Vector3(-1, 0, 0);
}
Vector3 Vector3::Right(float value)
{
	return Right() * value;
}
Vector3 Vector3::Left()
{
	return Vector3(1, 0, 0);
}
Vector3 Vector3::Left(float value)
{
	return Left() * value;
}
Vector3 Vector3::Forward()
{
	return Vector3(0, 0, 1);
}
Vector3 Vector3::Forward(float value)
{
	return Forward() * value;
}
Vector3 Vector3::Back()
{
	return Vector3(0, 0, -1);
}

Vector3 Vector3::Back(float value)
{
	return Back() * value;
}

void Vector3::MoveTowards(Vector3 target, float maxDistanceDelta)
{
	Vector3 vector3 = target - *this;
	float magnitude = vector3.Magnitude();
	Debug::Log(magnitude);
	if (magnitude <= maxDistanceDelta || magnitude == 0)
		*this = target;
	else
		*this += vector3 / magnitude * maxDistanceDelta;
}
Vector3 Vector3::Lerp(Vector3 target, float t)
{
	t = std::min(std::max(float(t), float(0)), float(1));
	return Vector3(x + (target.x - x) * t, y + (target.y - y) * t, z + (target.z - z) * t);
}

float Vector3::Distance(Vector3 target)
{
	Debug::Log((*this - target));
	return (*this - target).Magnitude();
}

float Vector3::SqrMagnitude()
{
	return x * x + y * y + z * z;
}
float Vector3::Magnitude()
{
	return sqrt(SqrMagnitude());
}

Vector3 Vector3::Normalized()
{
	Vector3 normalized = *this;
	normalized.Normalize();
	return normalized;
}
void Vector3::Normalize()
{
	float num = Magnitude();

	if (num != 0)
		*this = *this / num;
	else
		*this = Vector3();
}

bool Vector3::operator==(const Vector3 & other) const
{
	return x == other.x && y == other.y && z == other.z;
}
bool Vector3::operator!=(const Vector3 & other) const
{
	return !((*this) == other);
}

Vector3 Vector3::operator+(const Vector3 & other)
{
	return Vector3(x + other.x, y + other.y, z + other.z);
}
Vector3 Vector3::operator-(const Vector3 & other)
{
	return Vector3(x - other.x, y - other.y, z - other.z);
}
Vector3 Vector3::operator*(const Vector3 & other)
{
	return Vector3(x * other.x, y * other.y, z * other.z);
}
Vector3 Vector3::operator/(const Vector3 & other)
{
	if (other.x == 0 || other.y == 0 || other.z == 0)
	{
		Debug::Error("Trying to divide vector by 0");
		return Vector3(0, 0, 0);
	}

	return Vector3(x / other.x, y / other.y, z / other.z);
}

Vector3 Vector3::operator+(const float & number)
{
	return Vector3(x + number, y + number, z + number);
}
Vector3 Vector3::operator-(const float & number)
{
	return Vector3(x - number, y - number, z - number);
}
Vector3 Vector3::operator*(const float & number)
{
	return Vector3(x * number, y * number, z * number);
}
Vector3 Vector3::operator/(const float & number)
{
	if (number == 0 || number == 0 || number == 0)
	{
		Debug::Error("Trying to divide vector by 0");
		return Vector3(0, 0, 0);
	}

	return Vector3(x / number, y / number, z / number);
}

Vector3 & Vector3::operator+=(const Vector3 & other)
{
	*this = *this + other;
	return *this;
}
Vector3 & Vector3::operator-=(const Vector3 & other)
{
	*this = *this - other;
	return *this;
}
Vector3 & Vector3::operator*=(const Vector3 & other)
{
	*this = *this * other;
	return *this;
}
Vector3 & Vector3::operator/=(const Vector3 & other)
{
	*this = *this / other;
	return *this;
}

Vector3 & Vector3::operator+=(const float & number)
{
	*this = *this + number;
	return *this;
}
Vector3 & Vector3::operator-=(const float & number)
{
	*this = *this - number;
	return *this;
}
Vector3 & Vector3::operator*=(const float & number)
{
	*this = *this * number;
	return *this;
}
Vector3 & Vector3::operator/=(const float & number)
{
	*this = *this / number;
	return *this;
}

Vector3 Vector3::operator!()
{
	return Vector3(-x, -y, -z);
}

Vector3::operator std::string() const
{
	return "(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ")";
}