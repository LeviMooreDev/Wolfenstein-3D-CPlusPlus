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
};

