#include "Engine.h"
#include <GL/freeglut.h>
#include <GLFW\glfw3.h>
#include <iostream>
#include <windows.h>
#include "Time.h"
#include "Debug.h"
#include "Input.h"
#include "Transform.h"

GLFWwindow* window;

void KeyInputCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS)
		Input::EventCollectDown(key);

	if (action == GLFW_RELEASE)
		Input::EventCollectUp(key);
}

void ResizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

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
	window = glfwCreateWindow(weight, height, name.c_str(), NULL, NULL);

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

	Input::Setup();

	//run start method
	start(this);

	while (!glfwWindowShouldClose(window))
	{
		Time::Update();

		if (activeScene == nullptr)
		{
			glClearColor(1, 1, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			return;
		}
		if (activeScene->GetActiveCamera() != nullptr)
		{
			Camera * camera = activeScene->GetActiveCamera();
			
			//clear scene
			glClearColor(camera->backgroundColor.R1(), camera->backgroundColor.G1(), camera->backgroundColor.B1(), camera->backgroundColor.A1());
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			//set perspective
			glMatrixMode(GL_PROJECTION_MATRIX);
			glLoadIdentity();
			gluPerspective(camera->fov, (double)weight / (double)height, camera->nearClip, camera->farClip);

			//not sure maybe camera #########
			glMatrixMode(GL_MODELVIEW_MATRIX);

			Vector3 cameraPosition = camera->GetParentGameObject()->transform.position;
			glTranslatef(cameraPosition.x, cameraPosition.y, cameraPosition.z);
		}

		gameLoop(this);
		activeScene->UpdateGameObjects();

		if (activeScene->GetActiveCamera() != nullptr)
		{
			//update/draw screen
			glfwSwapBuffers(window);
		}

		//check for input
		Input::PreEventCollect();
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

void Engine::Close()
{
	glfwSetWindowShouldClose(window, GL_TRUE);
}