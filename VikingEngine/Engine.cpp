#include "Engine.h"
#include <GL/freeglut.h>
#include <GLFW\glfw3.h>
#include <iostream>
#include <windows.h>

///////////////////////////

void KeyInputCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS)
		if (key == GLFW_KEY_ESCAPE)
			glfwSetWindowShouldClose(window, GL_TRUE);
}
void ResizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

///////////////////////////


Engine::Engine(string name, int weight, int height, void(*start)(Engine *), void(*gameLoop)(Engine *))
{
	//initialize GLFW
	if (!glfwInit())
	{
		MessageBoxA(NULL, "Failed to initialize GLFW.", "Error", 0x00000000L);
		return;
	}

	//4x antialiasing
	glfwWindowHint(GLFW_SAMPLES, 4);

	//open a glfw window
	GLFWwindow* window = glfwCreateWindow(weight, height, name.c_str(), NULL, NULL);

	if (window == NULL)
	{
		MessageBoxA(NULL, "Failed to open GLFW window.", "Error", 0x00000000L);
		glfwTerminate();
		return;
	}

	//set window context
	glfwMakeContextCurrent(window);

	//set viewport
	glViewport(0, 0, weight, height);
	glfwSetFramebufferSizeCallback(window, ResizeCallback);

	//setup key callback
	glfwSetKeyCallback(window, KeyInputCallback);

	glEnable(GL_DEPTH_TEST); // Depth Testing
	glDepthFunc(GL_LEQUAL);
	glDisable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	//run start method
	start(this);

	while (!glfwWindowShouldClose(window))
	{
		//clear scene
		glClearColor(0.1, 0.1, 0.1, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//set perspective
		glMatrixMode(GL_PROJECTION_MATRIX);
		glLoadIdentity();
		gluPerspective(60, (double)weight / (double)height, 0.1, 100);

		//not sure maybe camera #########
		glMatrixMode(GL_MODELVIEW_MATRIX);
		glTranslatef(0, 0, -5);

		gameLoop(this);
		//if there is an active scene update all the game objects in it
		if (activeScene != nullptr)
		{
			activeScene->UpdateGameObjects();
		}

		//update/draw screen
		glfwSwapBuffers(window);

		//check for input
		glfwPollEvents();
	}

	//close window
	glfwDestroyWindow(window);
	glfwTerminate();
	
	return;
}
Engine::~Engine()
{
	delete activeScene;
}


