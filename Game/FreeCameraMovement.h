#pragma once
#include "Component.h"
#include "Transform.h"
#define FreeCameraMovementComponentName "Free Camera Movement"

//responsible for moving the free camera around
class FreeCameraMovement : public Component
{
private:
	//normal move speed
	float normalSpeed = 10;
	//fast move speed
	float fastSpeed = 30;
	//the current move speed
	float currentSpeed = 30;
	//mouse look speed
	float lookSpeed = 30;

public:

	//called by the engine every frame
	void Update(Scene * scene);

	//moves the camera with the keyboard
	void Move();

	//rotates the camera with the mouse
	void Look();

	//returns the component name
	string GetName() { return FreeCameraMovementComponentName; };
};

