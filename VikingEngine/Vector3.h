#pragma once
#include "DLLHelper.h"

class DLLEXTERN Vector3
{
public:
	float x = 0;
	float y = 0;
	float z = 0;

	Vector3();
	Vector3(int x, int y, int z);
	~Vector3();
};

