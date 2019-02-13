#include "Camera.h"
#include "Scene.h"



Camera::Camera(bool setAsActive)
{
	(*this).setAsActive = setAsActive;
}
Camera::~Camera()
{
}

void Camera::Update(Scene * scene)
{
	if (setAsActive)
		scene->SetActiveCamera(this);
}
