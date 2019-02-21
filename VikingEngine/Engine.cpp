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

//declare static fields
Engine * Engine::i;

//the reason we define and declare window nad ResizeCallback() here and not in the header file is because if we did the project using our Engine.dll file would also need to include glfw3.lib and reeglut.lib
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

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

	//initialize GLFW
	if (!glfwInit())
	{
		MessageBoxA(NULL, "Failed to initialize GLFW.", "Error", 0x00000000L);
		return;
	}

	//render with 4x anti aliasing
	glfwWindowHint(GLFW_SAMPLES, 4);

	//set window width and height
	windowWidth = width;
	windowHeight = height;

	//open new glfw window
	window = glfwCreateWindow(windowWidth, windowHeight, name.c_str(), NULL, NULL);
	if (window == NULL)
	{
		MessageBoxA(NULL, "Failed to open GLFW window.", "Error", 0x00000000L);
		glfwTerminate();
		return;
	}

	//set glfw window context
	glfwMakeContextCurrent(window);

	//set viewport to fit our window size
	glViewport(0, 0, windowWidth, windowHeight);
	
	//set frame buffer size callback
	//when the window change size we update our viewport using ResizeCallback()
	glfwSetFramebufferSizeCallback(window, ResizeCallback);

	//enable blend and set blend function so we can have transparent textures
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//enable depth test by deafult and set depth function
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	//enable depth cull face by deafult and set it to front only
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);

	//setup input and audio classes
	Input::Setup(window);
	Audio::Setup();

	//run game start method
	start();

	//while we still want the game window to be open
	while (!glfwWindowShouldClose(window))
	{
		//update time class
		Time::UpdateDeltaTime();

		//reset matrix
		glLoadIdentity();
		glDepthMask(true);

		//if there is an active scene
		if (activeScene != nullptr)
		{
			//update game objects
			activeScene->Update();
			//draw game objects
			activeScene->Draw();

			//reset matrix
			glLoadIdentity();
			//draw ui
			activeScene->UI();
		}

		//show the new frame on screen
		glfwSwapBuffers(window);

		//call game loop method
		gameLoop();

		//update input class
		Input::ResetInput();
	}

	//when we are done close the window
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
