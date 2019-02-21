#pragma once
#include "DLLHelper.h"
#include "GameObject.h"
#include "Vector2.h"
#include "Vector3.h"

class DLLEXTERN Raycast
{
public:
	//send out a ray in 3d world space that returns the game object it hits
	//rayOrigin: the origin position of the ray
	//rayDir: the direction the ray is moving
	//point: the exact point the ray hits 
	//ignore: the game object the ray should ignore
	static GameObject * Send(Vector3 rayOrigin, Vector3 rayDir, Vector3 & point, GameObject * ignore);
};

