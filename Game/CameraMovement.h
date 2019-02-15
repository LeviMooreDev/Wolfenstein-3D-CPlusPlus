#pragma once
#include "Component.h"
#include "Transform.h"

class CameraMovement : public Component
{
private:
	float cameraSpeed = 10;
	float lookSpeed = 30;

public:
	CameraMovement();
	~CameraMovement();
	
	void Update(Scene * scene);
	void Move();
	void Look();
};

