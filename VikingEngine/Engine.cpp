#include "Engine.h"
#include <GLFW\glfw3.h>
#include <iostream>
#include <windows.h>

void size_resize_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

Engine::Engine(string name, int weight, int height, void(*start)(Engine *), void(*gameLoop)(Engine *))
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

	GLFWwindow* window = glfwCreateWindow(weight, height, name.c_str(), NULL, NULL);
	if (window == NULL)
	{
		MessageBoxA(NULL, "Not able to create OpenGL window", "VikignEngine Error", 0x00000000L);
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(window);
	glViewport(0, 0, weight, height);
	glfwSetFramebufferSizeCallback(window, size_resize_callback);

	start(this);
	while (!glfwWindowShouldClose(window))
	{
		gameLoop(this);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);  //Sætter baggrundfarven
		glClear(GL_COLOR_BUFFER_BIT); //Nul stiller baggrunden til baggrundsfarven

		glBegin(GL_TRIANGLES);
		glVertex3f(-0.5f, 0.0f, 0.0f);
		glVertex3f(0.0f, 0.5f, 0.0f);
		glVertex3f(0.5f, 0.0f, 0.0f);
		glEnd();

		glfwSwapBuffers(window); //Bruger dobbelt buffer koncept til reducering af flicker - her byttes bufferne
		glfwPollEvents(); //Kalder evt. callback der skal reagere på keyboard eller mouse input
	}
	glfwTerminate();
}
Engine::~Engine()
{
}