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
#include "Audio.h"

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
	glfwWindowHint(GLFW_SAMPLES, 4);

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

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);

	Input::Setup(window);
	Audio::Setup();

	//run start method
	start();

	while (!glfwWindowShouldClose(window))
	{
		Time::Update();


		glLoadIdentity();
		glDepthMask(true);

		if (activeScene != nullptr)
		{
			activeScene->Update();
			activeScene->Draw();

			glLoadIdentity();
			activeScene->UI();
		}

		glfwSwapBuffers(window);

		gameLoop();
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
