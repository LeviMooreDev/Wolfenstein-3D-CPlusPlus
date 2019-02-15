#pragma once
#include "DLLHelper.h"
#include "Vector3.h"

class Transform
{
private:

public:
	Vector3 position;
	Vector3 scale;
	Vector3 rotation;

	DLLEXTERN Transform();
	DLLEXTERN ~Transform();

	DLLEXTERN Vector3 Up();
	DLLEXTERN Vector3 Down();
	DLLEXTERN Vector3 Right();
	DLLEXTERN Vector3 Left();
	DLLEXTERN Vector3 Forward();
	DLLEXTERN Vector3 Back();
};