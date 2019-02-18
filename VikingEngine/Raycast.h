#pragma once
#include "DLLHelper.h"
#include "GameObject.h"
#include "Vector2.h"
#include "Vector3.h"

class DLLEXTERN Raycast
{
public:
	static GameObject * Send(Vector3 rayOrigin, Vector3 rayDir, Vector3 & point, GameObject * ignore);
};

