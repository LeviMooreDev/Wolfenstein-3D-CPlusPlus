#include <iostream>
#include <Windows.h>
#include <Engine.h>
#include "Game.h"

Game game;

void Start()
{
	//relay engine start call to our game
	game.Start();
}

void GameLoop()
{
	//relay engine game loop call to our game
	game.GameLoop();
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	//create a new engine we can use with our game
	//the reason we don't have the game code in Porgram.cpp is that we want to use things like static methods which requires a class.
	new Engine("Wolfenstein Real 3D", 800, 600, &Start, &GameLoop);
	return 0;
}