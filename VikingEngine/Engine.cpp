#include "Engine.h"
#include <GL/freeglut.h>
#include <GLFW\glfw3.h>
#include <iostream>
#include <windows.h>
#include "Time.h"
#include "Debug.h"
#include "Input.h"
#include "Transform.h"
#include "Vector2.h"

Engine * Engine::i;
GLFWwindow* window;

void ResizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

Engine * Engine::I()
{
	return i;
}

Engine::Engine(string name, int width, int height, void (*start)(), void (*gameLoop)())
{
	i = this;
	//initialize GLFW
	if (!glfwInit())
	{
		MessageBoxA(NULL, "Failed to initialize GLFW.", "Error", 0x00000000L);
		return;
	}

	//4x antialiasing
	glfwWindowHint(GLFW_SAMPLES, 16);

	windowWidth = width;
	windowHeight = height;

	//open a glfw window
	window = glfwCreateWindow(windowWidth, windowHeight, name.c_str(), NULL, NULL);

	if (window == NULL)
	{
		MessageBoxA(NULL, "Failed to open GLFW window.", "Error", 0x00000000L);
		glfwTerminate();
		return;
	}

	//set window context
	glfwMakeContextCurrent(window);

	//set viewport
	glViewport(0, 0, windowWidth, windowHeight);
	glfwSetFramebufferSizeCallback(window, ResizeCallback);

	glEnable(GL_DEPTH_TEST); // Depth Testing
	glDepthFunc(GL_LEQUAL);
	glDisable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	Input::Setup(window);

	//run start method
	start();

	while (!glfwWindowShouldClose(window))
	{
		Time::Update();

		if (activeScene == nullptr)
		{
			glClearColor(1, 1, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			return;
		}

		gameLoop();
		glLoadIdentity();
		activeScene->UpdateGameObjects();
		activeScene->DrawCamera();
		activeScene->DrawGameObjects();

		glfwSwapBuffers(window);

		Input::EndLoop();
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

void Engine::Close()
{
	glfwSetWindowShouldClose(window, GL_TRUE);
}

Vector2 Engine::GetWindowSize()
{
	return Vector2((float)windowWidth, (float)windowHeight);
}
