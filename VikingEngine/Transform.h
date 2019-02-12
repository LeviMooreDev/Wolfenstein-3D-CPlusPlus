#pragma once
#include "DLLHelper.h"
#include "Vector3.h"

class DLLEXTERN Transform
{
private:

public:
	Vector3 position;
	Vector3 scale;
	Vector3 rotation;

	Transform();
	~Transform();
};

