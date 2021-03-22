#include <algorithm>
#include <iostream>
#include <string>
#include "Vector2.h"
#include "Debug.h"
typedef std::basic_string<char> string;

Vector2::Vector2(float x, float y)
{
	(*this).x = x;
	(*this).y = y;
}

Vector2 Vector2::One()
{
	return Vector2(1, 1);
}
Vector2 Vector2::One(float value)
{
	return One() * value;
}
Vector2 Vector2::Up()
{
	return Vector2(0, -1);
}
Vector2 Vector2::Up(float value)
{
	return Up() * value;
}
Vector2 Vector2::Down()
{
	return Vector2(0, 1);
}
Vector2 Vector2::Down(float value)
{
	return Down() * value;
}
Vector2 Vector2::Right()
{
	return Vector2(-1, 0);
}
Vector2 Vector2::Right(float value)
{
	return Right() * value;
}
Vector2 Vector2::Left()
{
	return Vector2(1, 0);
}
Vector2 Vector2::Left(float value)
{
	return Left() * value;
}

void Vector2::MoveTowards(Vector2 target, float maxDistanceDelta)
{
	Vector2 Vector2 = target - *this;
	float magnitude = Vector2.Magnitude();

	if (magnitude <= maxDistanceDelta || magnitude == 0)
		*this = target;
	else
		*this += Vector2 / magnitude * maxDistanceDelta;
}

Vector2 Vector2::Lerp(Vector2 target, float t)
{
	t = std::min(std::max(float(t), float(0)), float(1));
	return Vector2(x + (target.x - x) * t, y + (target.y - y) * t);
}

float Vector2::Distance(Vector2 target)
{
	return (*this - target).Magnitude();
}

float Vector2::SqrMagnitude()
{
	return x * x + y * y;
}

float Vector2::Magnitude()
{
	return sqrt(SqrMagnitude());
}

Vector2 Vector2::Normalized()
{
	Vector2 normalized = *this;
	normalized.Normalize();
	return normalized;
}

void Vector2::Normalize()
{
	float num = Magnitude();

	if (num != 0)
		*this = *this / num;
	else
		*this = Vector2();
}

bool Vector2::operator==(const Vector2 & other) const
{
	return x == other.x && y == other.y;
}
bool Vector2::operator!=(const Vector2 & other) const
{
	return !((*this) == other);
}

Vector2 Vector2::operator+(const Vector2 & other)
{
	return Vector2(x + other.x, y + other.y);
}
Vector2 Vector2::operator-(const Vector2 & other)
{
	return Vector2(x - other.x, y - other.y);
}
Vector2 Vector2::operator*(const Vector2 & other)
{
	return Vector2(x * other.x, y * other.y);
}
Vector2 Vector2::operator/(const Vector2 & other)
{
	if (other.x == 0 || other.y == 0)
	{
		Debug::Error("Trying to divide vector by 0");
		return Vector2(0, 0);
	}

	return Vector2(x / other.x, y / other.y);
}

Vector2 Vector2::operator+(const float & number)
{
	return Vector2(x + number, y + number);
}
Vector2 Vector2::operator-(const float & number)
{
	return Vector2(x - number, y - number);
}
Vector2 Vector2::operator*(const float & number)
{
	return Vector2(x * number, y * number);
}
Vector2 Vector2::operator/(const float & number)
{
	if (number == 0 || number == 0 || number == 0)
	{
		Debug::Error("Trying to divide vector by 0");
		return Vector2(0, 0);
	}

	return Vector2(x / number, y / number);
}

Vector2 & Vector2::operator+=(const Vector2 & other)
{
	*this = *this + other;
	return *this;
}
Vector2 & Vector2::operator-=(const Vector2 & other)
{
	*this = *this - other;
	return *this;
}
Vector2 & Vector2::operator*=(const Vector2 & other)
{
	*this = *this * other;
	return *this;
}
Vector2 & Vector2::operator/=(const Vector2 & other)
{
	*this = *this / other;
	return *this;
}

Vector2 & Vector2::operator+=(const float & number)
{
	*this = *this + number;
	return *this;
}
Vector2 & Vector2::operator-=(const float & number)
{
	*this = *this - number;
	return *this;
}
Vector2 & Vector2::operator*=(const float & number)
{
	*this = *this * number;
	return *this;
}
Vector2 & Vector2::operator/=(const float & number)
{
	*this = *this / number;
	return *this;
}

Vector2 Vector2::operator!()
{
	return Vector2(-x, -y);
}

Vector2::operator std::string() const
{
	return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
}