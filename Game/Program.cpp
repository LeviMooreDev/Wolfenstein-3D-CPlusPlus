#include <iostream>
#include <Windows.h>
#include <Engine.h>
#include <Scene.h>
#include <GameObject.h>
#include <Debug.h>
#include <MeshRenderer.h>


Scene * testScene;
GameObject * go;

//runs once when the game start
void Start(Engine * engine)
{
	testScene = new Scene();
	engine->activeScene = testScene;
	
	go = new GameObject();
	//go->transform.SetPosition(new Vector3(1.5, 0, -7));
	go->transform.SetPosition(new Vector3(1, 0, 2));
	go->AddComponent(new MeshRenderer());

	testScene->AddGameObject(go);
}

//runs every frame
void GameLoop(Engine * engine)
{
	//go->transform.position.x+=0.001;
}

//where the program enters
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	new Engine("Game Name", 800, 600, &Start, &GameLoop);
	return 0;
}