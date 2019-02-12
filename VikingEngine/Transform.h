#pragma once
#include "DLLHelper.h"
#include "Vector3.h"

class DLLEXTERN Transform
{
private:
	Vector3 * position;
	Vector3 * scale;
	Vector3 * rotating;

public:
	Transform();
	~Transform();

	void SetPosition(Vector3 * vector);
	Vector3 GetPosition();
	void SetScale(Vector3 * vector);
	Vector3 GetScale();
	void SetRotating(Vector3 * vector);
	Vector3 GetRotating();
};

