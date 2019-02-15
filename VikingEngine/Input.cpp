#pragma once
#include "Input.h"
#include <GLFW\glfw3.h>
#include "Debug.h"
#include <iostream> 
#include <iterator> 
#include <map>
#include "Engine.h"

Vector2 Input::currentMousePosition;
Vector2 Input::lastMousePosition;
GLFWwindow * Input::window;
std::map<int, bool> Input::hold = std::map<int, bool>();
std::map<int, bool> Input::down = std::map<int, bool>();
std::map<int, bool> Input::up	= std::map<int, bool>();

bool Input::KeyUp(Keys key)
{
	return Input::up[key];
}
bool Input::KeyDown(Keys key)
{
	return Input::down[key];
}
bool Input::KeyHold(Keys key)
{
	return Input::hold[key];
}

Vector2 Input::MousePosition()
{
	return currentMousePosition;
}

Vector2 Input::MouseMoveDirection()
{
	return (currentMousePosition - lastMousePosition);
}

void Input::ShowCursor()
{
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void Input::HideCursor()
{
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Input::KeyInputCallback(GLFWwindow * window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		Input::down[key] = true;
		Input::hold[key] = true;
	}
	if (action == GLFW_RELEASE)
	{
		Input::up[key] = true;
		Input::hold[key] = false;
	}
}
void Input::CursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
{
	currentMousePosition = Vector2((float)xpos, Engine::I()->GetWindowSize().y - (float)ypos);
}

void Input::Setup(GLFWwindow * window)
{
	Input::window = window;
	glfwSetKeyCallback(window, Input::KeyInputCallback);
	glfwSetCursorPosCallback(window, CursorPositionCallback);

	for (int i = Input::Keys::A; i != Input::Keys::MENU; i++)
	{
		Input::Keys key = static_cast<Input::Keys>(i);
		Input::hold.insert(std::pair<int, bool>((int)key, false));
		Input::down.insert(std::pair<int, bool>((int)key, false));
		Input::up.insert(std::pair<int, bool>((int)key, false));
	}
}

void Input::EndLoop()
{
	//keys
	std::map<int, bool>::iterator c_itr;
	for (c_itr = down.begin(); c_itr != down.end(); ++c_itr)
	{
		Input::down[c_itr->first] = false;
	}
	for (c_itr = up.begin(); c_itr != up.end(); ++c_itr)
	{
		Input::up[c_itr->first] = false;
	}

	//mouse
	lastMousePosition = currentMousePosition;

	glfwPollEvents();
}