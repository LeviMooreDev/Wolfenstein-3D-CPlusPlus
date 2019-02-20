#pragma once
#include "DLLHelper.h"
#include "Component.h"
#include "GameObject.h"
#include "Color.h"

class Camera : public Component
{
private:
	void Draw1(Scene * scene);

public:
	Color backgroundColor;
	int fov = 90;
	float nearClip = 0.1f;
	float farClip = 100.0f;

	DLLEXTERN Camera(bool use = false);
	DLLEXTERN ~Camera();

	string GetName() { return "Camera"; };
};

