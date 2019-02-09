#include <iostream>
#include <Windows.h>
#include <Engine.h>
#include <Scene.h>
#include <GameObject.h>
#include <Debug.h>

Scene scene;
void Start(Engine * engine)
{
	engine->activeScene = scene;
}

void GameLoop(Engine * engine)
{
	GameObject go;
	scene.AddGameObject(go);
	scene.ClearGameObjects();
	Debug::Log(scene.GetGameObjectCount());
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	new Engine("Game Name", 800, 600, &Start, &GameLoop);
	return 0;
}