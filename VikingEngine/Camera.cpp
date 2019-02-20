#include "Camera.h"
#include <GL/freeglut.h>
#include <GLFW\glfw3.h>
#include "Scene.h"
#include "Engine.h"
#include <algorithm>
#include <algorithm>



Camera::Camera(bool use)
{
}
Camera::~Camera()
{
}

void Camera::Draw1(Scene * scene)
{
	if (scene->activeCamera != this)
		return;

	//set perspective
	glMatrixMode(GL_PROJECTION_MATRIX);
	gluPerspective(fov, (double)Engine::I()->GetWindowSize().x / (double)Engine::I()->GetWindowSize().y, nearClip, farClip);
	glMatrixMode(GL_MODELVIEW_MATRIX);
	
	glClearColor(backgroundColor.R1(), backgroundColor.G1(), backgroundColor.B1(), backgroundColor.A1());
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//rotation
	glRotatef(gameObject->transform.rotation.x, 1, 0, 0);
	glRotatef(gameObject->transform.rotation.y, 0, 1, 0);
	glRotatef(gameObject->transform.rotation.z, 0, 0, 1);

	//position
	glTranslatef(-gameObject->transform.position.x, -gameObject->transform.position.y, gameObject->transform.position.z);
}