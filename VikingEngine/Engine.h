#pragma once
#include "DLLHelper.h"
#include "Scene.h"
#include <iostream>

typedef std::basic_string<char> string;

class DLLEXTERN Engine
{
public:
	//the scene that is rendered
	Scene * activeScene;

	Engine(string name, int height, int weight, void(*start)(Engine *), void(*gameLoop)(Engine *));
	~Engine();
};

