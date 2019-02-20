#pragma once
#include "DLLHelper.h"
#include "Scene.h"
#include <iostream>
#include "Camera.h"
#include "Vector2.h"

typedef std::basic_string<char> string;

class Engine
{
private:
	static Engine * i;
	int windowWidth;
	int windowHeight;

public:
	Scene * activeScene;
	DLLEXTERN static Engine * I();

	DLLEXTERN Engine(string name, int height, int width, void (*start)(), void (*gameLoop)());
	DLLEXTERN ~Engine();

	DLLEXTERN void Close();

	DLLEXTERN Vector2 GetWindowSize();
};

