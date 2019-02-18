#pragma once
#include "Component.h"
#include "Transform.h"

class FreeCameraMovement : public Component
{
private:
	float normalSpeed = 10;
	float fastSpeed = 30;
	float currentSpeed = 30;
	float lookSpeed = 30;

public:
	FreeCameraMovement();
	~FreeCameraMovement();
	
	void Update(Scene * scene);
	void Move();
	void Look();
};

