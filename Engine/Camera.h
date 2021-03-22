#pragma once
#include "DLLHelper.h"
#include "Component.h"
#include "GameObject.h"
#include "Color.h"
#define CameraComponentName "Camera"

//responsible for calculating the viewport from which the game is rendered
//the camera component is called before all other components
class Camera : public Component
{
private:
	//is called on the first draw call
	void Draw1(Scene * scene);

public:
	//background color
	Color backgroundColor;
	//field of view
	int fov = 90;
	//distance from the camera the game will begin to render
	float nearClip = 0.1f;
	//how far from the camera the game will render
	float farClip = 100.0f;

	DLLEXTERN Camera() {};

	//returns the component name
	string GetName() { return CameraComponentName; };
};

