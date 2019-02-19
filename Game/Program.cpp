#include <iostream>
#include <Windows.h>
#include <Engine.h>
#include "Game.h"

Game game;

void Start()
{
	game.Start();
}

void GameLoop()
{
	game.GameLoop();
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	new Engine("Wolfenstein Real 3D", 800, 600, &Start, &GameLoop);
	return 0;
}