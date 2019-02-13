#pragma once
#include "DLLHelper.h"
#include "Scene.h"
#include <iostream>
#include "Camera.h"

typedef std::basic_string<char> string;

class Engine
{
public:
	//the scene that is rendered
	Scene * activeScene;

	DLLEXTERN Engine(string name, int height, int weight, void(*start)(Engine *), void(*gameLoop)(Engine *));
	DLLEXTERN ~Engine();

	DLLEXTERN void Close();
};

