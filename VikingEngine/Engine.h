#pragma once
#include "DLLHelper.h"
#include "Scene.h"
#include <iostream>
#include "Camera.h"
#include "Vector2.h"

typedef std::basic_string<char> string;

//responsible for keeping the game running and together with scene making sure things are called in the right order
class Engine
{
private:
	//static pointer to the engine object
	static Engine * i;

	//width of the game window
	int windowWidth;
	//height of the game window
	int windowHeight;

public:
	//the active scene being rendered
	Scene * activeScene;

	//returns pointer to engine object
	DLLEXTERN static Engine * I();

	//name: name of the game
	//height: height of the game window
	//width: width of the game window
	//start: method to call when the game starts
	//gameLoop: method to call at the end of every frame
	DLLEXTERN Engine(string name, int height, int width, void (*start)(), void (*gameLoop)());
	DLLEXTERN ~Engine();

	//close the game
	DLLEXTERN void Close();

	//returns the size of the game window
	DLLEXTERN Vector2 GetWindowSize();
};

