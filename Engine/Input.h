#pragma once
#include "DLLHelper.h"
#include "Vector2.h"
#include <iostream> 
#include <iterator> 
#include <map>

//we create empty GLFWwindow class because we need it as a parameter, but if we include it the project using our Engine.dll file would also need to include glfw3.lib and reeglut.lib

struct GLFWwindow;

class Input
{
private:
	//that register the input and send it to us
	static GLFWwindow * window;

	//current mouse position
	static Vector2 currentMousePosition;
	//last mouse position
	static Vector2 lastMousePosition;
	//map of all keys and if one is being held down the value is true
	static std::map<int, bool> hold;
	//map of all keys and if one has been pressed this frame the value is true
	static std::map<int, bool> down;
	//map of all keys and if one has been released this frame the value is true
	static std::map<int, bool> up;
	//true if the left mouse button was clicked this frame
	static bool mouseLeftClicked;

	//callback method receiving all keyboard events
	static void KeyInputCallback(GLFWwindow * window, int key, int scancode, int action, int mods);
	//callback method receiving all mouse movement events
	static void CursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
	//callback method receiving all mouse click events
	static void MouseClickCallback(GLFWwindow* window, int button, int action, int mods);

public:
	//enum with all the keys the player can check with
	enum Keys
	{
		A = 65,
		B = 66,
		C = 67,
		D = 68,
		E = 69,
		F = 70,
		G = 71,
		H = 72,
		I = 73,
		J = 74,
		K = 75,
		L = 76,
		M = 77,
		N = 78,
		O = 79,
		P = 80,
		Q = 81,
		R = 82,
		S = 83,
		T = 84,
		U = 85,
		V = 86,
		W = 87,
		X = 88,
		Y = 89,
		Z = 90,
		N0 = 48,
		N1 = 49,
		N2 = 50,
		N3 = 51,
		N4 = 52,
		N5 = 53,
		N6 = 54,
		N7 = 55,
		N8 = 56,
		N9 = 57,
		KP_0 = 320,
		KP_1 = 321,
		KP_2 = 322,
		KP_3 = 323,
		KP_4 = 324,
		KP_5 = 325,
		KP_6 = 326,
		KP_7 = 327,
		KP_8 = 328,
		KP_9 = 329,
		F1 = 290,
		F2 = 291,
		F3 = 292,
		F4 = 293,
		F5 = 294,
		F6 = 295,
		F7 = 296,
		F8 = 297,
		F9 = 298,
		F10 = 299,
		F11 = 300,
		F12 = 301,
		F13 = 302,
		F14 = 303,
		F15 = 304,
		F16 = 305,
		F17 = 306,
		F18 = 307,
		F19 = 308,
		F20 = 309,
		F21 = 310,
		F22 = 311,
		F23 = 312,
		F24 = 313,
		F25 = 314,
		SPACE = 32,
		APOSTROPHE = 39,
		COMMA = 44,
		MINUS = 45,
		PERIOD = 46,
		SLASH = 47,
		SEMICOLON = 59,
		EQUAL = 61,
		LEFT_BRACKET = 91,
		BACKSLASH = 92,
		RIGHT_BRACKET = 93,
		GRAVE_ACCENT = 96,
		WORLD_1 = 161,
		WORLD_2 = 162,
		ESCAPE = 256,
		ENTER = 257,
		TAB = 258,
		BACKSPACE = 259,
		INSERT = 260,
		RIGHT = 262,
		LEFT = 263,
		DOWN = 264,
		UP = 265,
		PAGE_UP = 266,
		PAGE_DOWN = 267,
		HOME = 268,
		END = 269,
		CAPS_LOCK = 280,
		SCROLL_LOCK = 281,
		NUM_LOCK = 282,
		PRINT_SCREEN = 283,
		PAUSE = 284,
		KP_DECIMAL = 330,
		KP_DIVIDE = 331,
		KP_MULTIPLY = 332,
		KP_SUBTRACT = 333,
		KP_ADD = 334,
		KP_ENTER = 335,
		KP_EQUAL = 336,
		LEFT_SHIFT = 340,
		LEFT_CONTROL = 341,
		LEFT_ALT = 342,
		LEFT_SUPER = 343,
		RIGHT_SHIFT = 344,
		RIGHT_CONTROL = 345,
		RIGHT_ALT = 346,
		RIGHT_SUPER = 347,
		MENU = 348
	};

	//returns true of the key was active this frame
	DLLEXTERN static bool KeyHold(Keys key);
	//returns true of the key was released this frame
	DLLEXTERN static bool KeyDown(Keys key);
	//returns true of the key was pressed this frame
	DLLEXTERN static bool KeyUp(Keys key);

	//returns true if the left mouse button was clicked this frame
	DLLEXTERN static bool MouseLeftClick();
	//returns the mouse position
	DLLEXTERN static Vector2 MousePosition();
	//returns the direction the mouse is moving
	DLLEXTERN static Vector2 MouseMoveDirection();

	//show the mouse cursor
	DLLEXTERN static void ShowCursor();
	//hide the mouse cursor
	DLLEXTERN static void HideCursor();

	//does some work to make sure the input class is ready for use
	static void Setup(GLFWwindow * window);

	//reset user input
	static void ResetInput();
};